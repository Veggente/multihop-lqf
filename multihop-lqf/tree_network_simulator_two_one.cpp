//
//  tree_network_simulator_two_one.cpp
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#include "tree_network_simulator_two_one.h"
#include <random>
#include <iostream>
#include "generate_line_networks.h"  // NOLINT
#include "output_vector_to_file.h"  // NOLINT

int tree_network_simulator_two_one(int num_iterations, int output_period,
                                   const std::vector<double> &arrival_rate,
                                   const std::string &filename_lqf,
                                   const std::string &filename_bp) {
    // construct the network
    int num_links = 4;
    int interference_distance = 1;
    std::vector<std::vector<bool>> maximal_schedule_matrix =
        generateMatrixLinear(num_links, interference_distance);
    
    // run the iterations
    std::vector<int> queues_lqf(num_links, 0);  // queues for LQF
    std::vector<int> queues_bp(num_links, 0);  // queues for back-pressure
    std::mt19937 rng(static_cast<unsigned int>(0));  // random number generator
    std::vector<std::bernoulli_distribution> arrival_generator =
        bernoulli_distribution_vector(arrival_rate);  // Bernoulli distribution
                                                      // generator
    int percent = 0;
    for (int t = 0; t < num_iterations; ++t) {  // t is the time slot
        // Output to files
        if (t%output_period == 0) {
            output_vector_to_file(queues_lqf, filename_lqf);
            output_vector_to_file(queues_bp, filename_bp);
        }
        
        // Output to screen
        int new_percent = t*100/num_iterations;
        if (new_percent > percent) {
            std::cout << new_percent << "% completed!" << std::endl;
            percent = new_percent;
        }
        
        // Service and internal arrivals
        std::vector<bool> attempted_schedule_lqf = lqf(maximal_schedule_matrix,
                                                       queues_lqf, rng);
        std::vector<bool> attempted_schedule_bp = bp(maximal_schedule_matrix,
                                                     queues_bp, rng);
        std::vector<bool> actual_schedule_lqf = vector_intersection(
                                                                    attempted_schedule_lqf, queues_lqf);
        std::vector<bool> actual_schedule_bp = vector_intersection(
                                                                   attempted_schedule_bp, queues_bp);
        std::vector<bool> internal_arrival_lqf = vector_shift_forward(
                                                                      actual_schedule_lqf);
        std::vector<bool> internal_arrival_bp = vector_shift_forward(
                                                                     actual_schedule_bp);
        queues_lqf = vector_difference(queues_lqf, actual_schedule_lqf);
        queues_lqf = vector_sum(queues_lqf, internal_arrival_lqf);
        queues_bp = vector_difference(queues_bp, actual_schedule_bp);
        queues_bp = vector_sum(queues_bp, internal_arrival_bp);
    }
    return 0;
}