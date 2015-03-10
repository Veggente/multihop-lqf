//
//  general_network_simulator.cpp
//  multihop-lqf
//
//  Copyright (c) 2015 Xiaohan Kang. All rights reserved.
//

#include "general_network_simulator.h"
#include <iostream>
#include <cassert>
#include "bernoulli_arrival_process.h"
#include "output_vector_to_file.h"
#include "lqf.h"
#include "bp.h"
#include "vector_operations.h"

int general_network_simulator(
        const BoolMat &maximal_schedule_matrix,
        int64_t num_iterations,
        int64_t output_period,
        const Rates &arrival_rate,
        const std::string &filename_lqf,
        const std::string &filename_bp,
        std::mt19937 &rng,
        const IntVec &flow_map) {
    assert(!maximal_schedule_matrix.empty());
    int num_links = static_cast<int>(maximal_schedule_matrix[0].size());
    Queues queues_lqf(num_links, 0);
    Queues queues_bp(num_links, 0);
    BernDistVec arrival_generator =
        bernoulli_distribution_vector(arrival_rate);
    int percent = 0;
    for (int t = 0; t < num_iterations; ++t) {
        // Output to files.
        if (t%output_period == 0) {
            output_vector_to_file(queues_lqf, filename_lqf);
            output_vector_to_file(queues_bp, filename_bp);
        }
        // Progress bar.
        int new_percent = t*100/num_iterations;
        if (new_percent > percent) {
            std::cout << new_percent << "% completed!" << std::endl;
            percent = new_percent;
        }
        // Service and internal arrivals.
        BoolVec attempted_schedule_lqf = lqf(maximal_schedule_matrix,
                                             queues_lqf, rng);
        BoolVec attempted_schedule_bp = bp(maximal_schedule_matrix, flow_map,
                                           queues_bp, rng);
        BoolVec actual_schedule_lqf = vector_intersection(
            attempted_schedule_lqf, queues_lqf);
        BoolVec actual_schedule_bp = vector_intersection(
            attempted_schedule_bp, queues_bp);
        BoolVec internal_arrival_lqf = internal_arrival(actual_schedule_lqf,
                                                        flow_map);
        BoolVec internal_arrival_bp = internal_arrival(actual_schedule_bp,
                                                       flow_map);
        queues_lqf = vector_difference(queues_lqf, actual_schedule_lqf);
        queues_lqf = vector_sum(queues_lqf, internal_arrival_lqf);
        queues_bp = vector_difference(queues_bp, actual_schedule_bp);
        queues_bp = vector_sum(queues_bp, internal_arrival_bp);
        // Random exogenous arrivals.
        BoolVec exogenous_arrival = bernoulli_random_vector(arrival_generator,
                                                            rng);
        queues_lqf = vector_sum(queues_lqf, exogenous_arrival);
        queues_bp = vector_sum(queues_bp, exogenous_arrival);
    }
    std::cout << "Done!" << std::endl;
    return 0;
}
