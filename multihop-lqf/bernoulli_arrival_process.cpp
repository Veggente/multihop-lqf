//
//  bernoulli_arrival_process.cpp
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#include "bernoulli_arrival_process.h"  // NOLINT

std::vector<std::bernoulli_distribution> bernoulli_distribution_vector(
        const std::vector<double> &arrival_rate) {
    std::vector<std::bernoulli_distribution> b;
    for (int i = 0; i < arrival_rate.size(); ++i) {
        std::bernoulli_distribution bd(arrival_rate[i]);
        b.push_back(bd);
    }
    return b;
}

std::vector<bool> bernoulli_random_vector(
        std::vector<std::bernoulli_distribution> &bdv,
        std::minstd_rand &rng) {
    std::vector<bool> return_vector;  // NOLINT
    for (int i = 0; i < bdv.size(); ++i) {
        return_vector.push_back(bdv[i](rng));
    }
    return return_vector;
}

