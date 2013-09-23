//
//  compare_queue.h
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOP_LQF_COMPARE_QUEUE_H_
#define MULTIHOP_LQF_COMPARE_QUEUE_H_

#include <utility>

bool compQueue(const std::pair<double, int> &p1,
               const std::pair<double, int> &p2) {
    // for random tie-breaking in lqf()
    return (p1.first < p2.first);
}

#endif  // MULTIHOP_LQF_COMPARE_QUEUE_H_
