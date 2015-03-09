//
//  bp.h
//  multihop-lqf
//
//  Copyright (c) 2013, 2015 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOP_LQF_BP_H_
#define MULTIHOP_LQF_BP_H_

#include <random>
#include <utility>
#include <vector>
#include "./compare_queue.h"
#include "common.h"

// Back-pressure scheduling algorithm for linear networks: note that in this
// implementation when two adjacent queues are equal, the pressure is zero and
// the first queue is considered blocked; i.e., the back-pressure scheduling
// algorithm only schedule those with positive pressure.
template <typename Type>
std::vector<bool> bp(const std::vector<std::vector<bool>> &M,
                     const std::vector<Type> &q, std::mt19937 &g) {
    std::vector<bool> bp_schedule;

    // Calculate back-pressure
    std::vector<Type> pressure;
    std::vector<bool> block(q.size(), false);
    for (int i = 0; i < q.size(); ++i) {
        if (i < q.size()-1) {
            if (q[i] > q[i+1]) {
                pressure.push_back(q[i]-q[i+1]);
            } else {  // q[i] <= q[i+1], q[i] is blocked
                pressure.push_back(static_cast<Type>(0));
                block[i] = true;
            }
        } else {  // i == q.size()-1
            pressure.push_back(q[i]);
            if (q[i] <= static_cast<Type>(0)) {  // q[N-1] <= 0, q[N-1] blocked
                block[i] = true;
            }
        }
    }

    // Calculate weight under each maximal schedule
    std::vector<std::pair<Type, int>> weights;
    for (int i = 0; i < M.size(); ++i) {
        Type qsum = 0;
        for (int j = 0; j < q.size(); ++j) {
            if (M[i][j]) {
                qsum += pressure[j];
            }
        }
        std::pair<Type, int> p(qsum, i);
        weights.push_back(p);
    }

    // Shuffle the pairs
    shuffle(weights.begin(), weights.end(), g);

    // Stable_sort the pairs
    stable_sort(weights.begin(), weights.end(), compQueue);

    // return the first schedule
    bp_schedule = M[(weights.back()).second];
    for (int i = 0; i < q.size(); ++i) {
        if (block[i]) {  // back-pressure does not schedule blocked queues
            bp_schedule[i] = false;
        }
    }
    return bp_schedule;
}

// Back-pressure scheduling algorithm for general networks. A flow map is
// required.
template <typename Type>
BoolVec bp(const BoolMat &M, const IntVec &flow_map, const std::vector<Type> &q,
           std::mt19937 &g) {
    BoolVec bp_schedule;
    // Calculate back-pressure.
    std::vector<Type> pressure;
    BoolVec block(q.size(), false);
    for (int i = 0; i < q.size(); ++i) {
        if (flow_map[i] != -1) {
            if (q[i] <= q[flow_map[i]]) {
                pressure.push_back(0);
                block[i] = true;
            } else {
                pressure.push_back(q[i]-q[flow_map[i]]);
            }
        } else {
            pressure.push_back(q[i]);
        }
    }
    // Calculate weight under each maximal schedule.
    std::vector<std::pair<Type, int>> weights;
    for (int i = 0; i < M.size(); ++i) {
        Type qsum = 0;
        for (int j = 0; j < q.size(); ++j) {
            if (M[i][j]) {
                qsum += pressure[j];
            }
        }
        std::pair<Type, int> p(qsum, i);
        weights.push_back(p);
    }
    // Shuffle the pairs.
    shuffle(weights.begin(), weights.end(), g);
    // Stable_sort the pairs.
    stable_sort(weights.begin(), weights.end(), compQueue);
    // return the first schedule.
    bp_schedule = M[(weights.back()).second];
    for (int i = 0; i < q.size(); ++i) {
        // back-pressure does not schedule blocked queues.
        if (block[i]) {
            bp_schedule[i] = false;
        }
    }
    return bp_schedule;
}

#endif  // MULTIHOP_LQF_BP_H_
