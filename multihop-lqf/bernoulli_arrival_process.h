//
//  bernoulli_arrival_process.h
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOPLQF_BERNOULLI_ARRIVAL_PROCESS_H_
#define MULTIHOPLQF_BERNOULLI_ARRIVAL_PROCESS_H_

#include <random>
#include <vector>

std::vector<std::bernoulli_distribution> bernoulli_distribution_vector(
        const std::vector<double> &arrival_rate);

std::vector<bool> bernoulli_random_vector(
        std::vector<std::bernoulli_distribution> &bdv, std::mt19937 &rng);

#endif  // MULTIHOPLQF_BERNOULLI_ARRIVAL_PROCESS_H_
