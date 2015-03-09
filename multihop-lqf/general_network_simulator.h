//
//  general_network_simulator.h
//  multihop-lqf
//
//  Copyright (c) 2015 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOP_LQF_GENERAL_NETWORK_SIMULATOR_H_
#define MULTIHOP_LQF_GENERAL_NETWORK_SIMULATOR_H_

#include "common.h"
#include <random>

// General network simulator with one-hop interference and Bernoulli arrivals.
// Longest-queue-first and back-pressure scheduling algorithms are used.
// All links have constant service rate of one packet per time slot. Output in
// files are queue lengths sampled at output periods.
int general_network_simulator(
        const BoolMat &maximal_schedule_matrix,
        int num_iterations,
        int output_period,
        const Rates &arrival_rate,
        const std::string &filename_lqf,
        const std::string &filename_bp,
        std::mt19937 &rng,
        const IntVec &flow_map);

#endif  //MULTIHOP_LQF_GENERAL_NETWORK_SIMULATOR_H_
