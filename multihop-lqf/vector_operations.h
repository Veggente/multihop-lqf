//
//  vector_operations.h
//  multihop-lqf
//
//  Copyright (c) 2013, 2015 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOP_LQF_VECTOR_OPERATIONS_H_
#define MULTIHOP_LQF_VECTOR_OPERATIONS_H_

#include <vector>
#include "common.h"

std::vector<bool> vector_intersection(const std::vector<bool> &v,
                                      const std::vector<int> &q);

std::vector<bool> vector_shift_forward(const std::vector<bool> &v);

std::vector<int> vector_sum(const std::vector<int> &v,
                            const std::vector<bool> &b);

std::vector<int> vector_difference(const std::vector<int> &v,
                                   const std::vector<bool> &b);

std::vector<int> vector_change_by_bool(const std::vector<int> &v,
                                       const std::vector<bool> &b,
                                       bool increase);

BoolVec internal_arrival(const BoolVec &departure, const IntVec &flow_map);

#endif  // MULTIHOP_LQF_VECTOR_OPERATIONS_H_
