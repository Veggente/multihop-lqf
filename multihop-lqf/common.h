//
//  common.h
//  multihop-lqf
//
//  Copyright (c) 2015 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOP_LQF_COMMON_H_
#define MULTIHOP_LQF_COMMON_H_

#include <vector>
#include <random>

typedef std::vector<std::vector<bool>> BoolMat;
typedef std::vector<bool> BoolVec;
typedef std::vector<double> Rates;
typedef std::vector<int64_t> Queues;
typedef std::vector<std::bernoulli_distribution> BernDistVec;
typedef std::vector<int> IntVec;

#endif  // MULTIHOP_LQF_COMMON_H_
