//
//  lqf.h
//  multihop-lqf
//
//  Copyright (c) 2013, 2015 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOP_LQF_LQF_H_
#define MULTIHOP_LQF_LQF_H_

#include <random>
#include <utility>
#include <vector>
#include <iostream>  // NOLINT
#include <algorithm>
#include "./compare_queue.h"

template <typename Type>  // LQF
std::vector<bool> lqf(const std::vector<std::vector<bool>> &M,
                      const std::vector<Type> &q, std::mt19937 &g) {
    // Make pairs of indices and queues
    std::vector<std::pair<Type, int>> queuePairs;
    for (int i = 0; i < q.size(); ++i) {
        std::pair<Type, int> p(q[i], i);
        queuePairs.push_back(p);
    }

    // Sort the pairs with random tie-breaking
    std::shuffle(queuePairs.begin(), queuePairs.end(), g);  // shuffle the pairs
    std::stable_sort(queuePairs.begin(), queuePairs.end(),
                compQueue);  // stable_sort the pairs according to the queue
                             // only

    // Find the suitable maximal schedule starting from the pair with longest
    // queue
    typename std::vector<std::pair<Type, int>>::const_reverse_iterator rit;
        // starting from large queues
    std::vector<int> survivor;  // indices of surviving maximal schedules
    std::vector<int> newSurvivor;  // temp for swapping
    for (int i = 0; i < M.size(); ++i) {  // indices are initialized 0 up to
                                          // size of M
        survivor.push_back(i);
    }
    for (rit = queuePairs.rbegin(); rit < queuePairs.rend(); ++rit) {
        if (survivor.size() == 1) {  // unique maximal schedule
            break;
        } else {
            newSurvivor.clear();
            newSurvivor.assign(survivor.begin(), survivor.end());
                // copy survivor to newSurvivor
            std::vector<int>::const_iterator it = newSurvivor.begin();
            while (it != newSurvivor.end()) {  // find compatible schedules
                if ( !( (M[*it])[rit->second] ) ) {
                    newSurvivor.erase(it);  // newSurvivor.size() decreases by 1
                } else {
                    ++it;  // it increases by 1
                }
            }
            if (newSurvivor.size() > 0) {  // if newSurvivor is not empty,
                                           // updated it to survivor
                survivor.swap(newSurvivor);
            }  // otherwise disregard newSurvivor
            newSurvivor.clear();
        }
    }

    // Check if there is only one survivor
    if (survivor.size() != 1) {
        std::cerr << "Error: Maximal matrix not simplified. Columns ";
        std::vector<int>::const_iterator it;
        for (it = survivor.begin(); it < survivor.end(); ++it) {
            if (it == survivor.end()-1) {
                std::cerr << "and ";
            }
            std::cerr << *it << " ";
        }
        std::cerr << "have the same vector.";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }

    // Return the unique schedule
    std::vector<bool> s(M[survivor.front()]);
    return s;
}

#endif  // MULTIHOP_LQF_LQF_H_
