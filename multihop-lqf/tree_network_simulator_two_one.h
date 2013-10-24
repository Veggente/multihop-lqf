//
//  tree_network_simulator_two_one.h
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOP_LQF_TREE_NETWORK_SIMULATOR_TWO_ONE_H_
#define MULTIHOP_LQF_TREE_NETWORK_SIMULATOR_TWO_ONE_H_

#include <vector>
#include <string>

// Tree network simulator with one-hop interference and Bernoulli arrivals.
// Longest-queue-first and back-pressure scheduling algorithms are used.
// All links have constant service rate of one packet per time slot. Output in
// files are queue lengths sampled at output periods.
int tree_network_simulator_two_one(int num_iterations,  // number of iterations
                           int output_period,  // period for file output
                           const std::vector<double> &arrival_rate,
                           // arrival rate vector
                           const std::string &filename_lqf,
                           // filename for LQF
                           const std::string &filename_bp);
                           // filename for back-pressure

#endif  // MULTIHOP_LQF_TREE_NETWORK_SIMULATOR_TWO_ONE_H_
