//
//  general_package.cpp
//  multihop-lqf
//
//  Copyright (c) 2015 Xiaohan Kang. All rights reserved.
//

#include "general_package.h"
#include <string>
#include <random>
#include "common.h"
#include "general_network_simulator.h"

int general_net_package(int argc, char * const argv[]) {
    int num_iterations = std::stoi(std::string(argv[1]));
    int output_period = std::stoi(std::string(argv[2]));
//    double arrival_rate_to_branch_one = std::stod(std::string(argv[3]));
//    double arrival_rate_to_branch_two = std::stod(std::string(argv[4]));
    double arrival_ratio = std::stod(std::string(argv[3]));
    std::string filename_lqf(argv[4]);
    std::string filename_bp(argv[5]);
    std::mt19937 rng(static_cast<unsigned int>(0));
    // A 2-1 tree network.
//    BoolVec m1{1, 1, 0};
//    BoolVec m2{0, 0, 1};
//    BoolMat maximal_schedule_matrix{m1, m2};
//    IntVec flow_map{2, -1, -1};
    // A 3-2 tree network.
//    BoolVec m1{1, 1, 0, 1, 0};
//    BoolVec m2{1, 0, 0, 0, 1};
//    BoolVec m3{0, 1, 1, 0, 0};
//    BoolVec m4{0, 0, 1, 0, 1};
//    BoolMat maximal_schedule_matrix{m1, m2, m3, m4};
//    IntVec flow_map{2, 4, 3, -1, -1};
    // A 4-1 tree network.
    BoolVec m1{1, 1, 0, 1, 0};
    BoolVec m2{1, 0, 0, 0, 1};
    BoolVec m3{0, 1, 1, 0, 0};
    BoolVec m4{0, 0, 1, 0, 1};
    BoolMat maximal_schedule_matrix{m1, m2, m3, m4};
    IntVec flow_map{2, -1, 3, 4, -1};
    // Three flows with uniformly adjustable rates.
    int num_links = static_cast<int>(maximal_schedule_matrix[0].size());
    Rates arrival_rates(num_links, 0.0);
    arrival_rates[0] = arrival_ratio;
    arrival_rates[1] = arrival_ratio;
    arrival_rates[2] = arrival_ratio;
    return general_network_simulator(maximal_schedule_matrix, num_iterations,
                                     output_period, arrival_rates, filename_lqf,
                                     filename_bp, rng, flow_map);
}
