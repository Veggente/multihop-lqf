//
//  generate_line_networks.h
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOPLQF_GENERATE_LINE_NETWORKS_H_
#define MULTIHOPLQF_GENERATE_LINE_NETWORKS_H_

#include <vector>

// Generate maximal schedule matrix M for line networks
std::vector<std::vector<bool>> generateMatrixLinear(int, int);

// Backtracking function used in generateMatrixLinear(int, int);
std::vector<std::vector<bool>> findMaximalLinear(int, int,
                                                 const std::vector<bool> &);
    // TODO add memoization

#endif  // MULTIHOPLQF_GENERATE_LINE_NETWORKS_H_
