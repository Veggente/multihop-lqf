//
//  generate_line_networks.cpp
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#include "./generate_line_networks.h"
#include <iostream>  // NOLINT

std::vector<std::vector<bool>> generateMatrixLinear(int N, int K) {
    std::vector<bool> d;
    return findMaximalLinear(N, K, d);
}

std::vector<std::vector<bool>> findMaximalLinear(
        int N, int K, const std::vector<bool> &decided) {
    std::vector<std::vector<bool>> maximal;  // reserved for output
    int decidedSize = static_cast<int>(decided.size());
    if (decidedSize > N) {
        std::cerr << "Error: Decided schedule size exceeds size of the linear"
                     "network!" << std::endl;
    } else if (decidedSize == N) {  // all is decided
        maximal.push_back(decided);
    } else {
        int lastOne = decidedSize-1;
        while ( (lastOne >= 0) && (!decided[lastOne]) ) {
            --lastOne;
        }  // lastOne is the position of the last 1 in decided
        bool addOne = 0;  // indicator of adding a 1 at end of decided
        bool addZero = 0;  // indicator of adding a 0 at end of decided
        if (lastOne < 0) {  // no 1's in decided
            addOne = 1;  // can always add 1
            if ( (K > decidedSize) && (decidedSize < N-1) ) {
                addZero = 1;  // can add 0 when the empty decided is not too
                              // large, and this is not the last link of the
                              // network
            }
        } else {  // some 1's in decided
            if (lastOne+K < decidedSize) {  // no 1 is close
                addOne = 1;
            }
            if (decidedSize < N-1) {
                if (lastOne+2*K >= decidedSize) {  // not end of network and the
                                                   // last 1 is not too far away
                    addZero = 1;
                }
            } else {
                addZero = !addOne;  // at the end of network, can either add
                                    // a 1 or a 0
            }
        }
        std::vector<std::vector<bool>> appendMaximal;
            // set of schedules to append
        std::vector<bool> nextDecided;  // next decided vector NOLINT
        if (addOne) {  // if a 1 can be added
            nextDecided = decided;
            nextDecided.push_back(1);
            appendMaximal = findMaximalLinear(N, K, nextDecided);
                // backtracking
            maximal.insert(maximal.end(), appendMaximal.begin(),
                           appendMaximal.end());
        }
        if (addZero) {  // if a 0 can be added
            nextDecided = decided;
            nextDecided.push_back(0);
            appendMaximal = findMaximalLinear(N, K, nextDecided);
                // backtracking
            maximal.insert(maximal.end(), appendMaximal.begin(),
                           appendMaximal.end());
        }
    }
    return maximal;
}
