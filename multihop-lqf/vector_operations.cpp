//
//  vector_intersection.cpp
//  multihop-lqf
//
//  Copyright (c) 2013, 2015 Xiaohan Kang. All rights reserved.
//

#include "vector_operations.h"  // NOLINT
#include <cassert>

std::vector<bool> vector_intersection(const std::vector<bool> &v,
                                      const std::vector<int> &q) {
    std::vector<bool> return_vector(v);
    for (int i = 0; i < q.size(); ++i) {
        if (q[i] <= 0) {
            return_vector[i] = false;
        }
    }
    return return_vector;
}

std::vector<bool> vector_shift_forward(const std::vector<bool> &v) {
    std::vector<bool> return_vector(1, false);
    return_vector.insert(return_vector.end(), v.begin(), v.end()-1);
    return return_vector;
}

std::vector<int> vector_sum(const std::vector<int> &v,
                            const std::vector<bool> &b) {
    return vector_change_by_bool(v, b, true);
}

std::vector<int> vector_difference(const std::vector<int> &v,
                                   const std::vector<bool> &b) {
    return vector_change_by_bool(v, b, false);
}

std::vector<int> vector_change_by_bool(const std::vector<int> &v,
                                       const std::vector<bool> &b,
                                       bool increase) {
    std::vector<int> return_vector(v);  // NOLINT
    for (int i = 0; i < return_vector.size(); ++i) {
        if (b[i]) {
            if (increase) {  // true in b[i] means increase by one
                ++return_vector[i];
            } else {  // true in b[i] means decrease by one
                --return_vector[i];
            }
        }
    }
    return return_vector;
}

BoolVec internal_arrival(const BoolVec &departure, const IntVec &flow_map) {
    int num_links = static_cast<int>(departure.size());
    BoolVec return_vec(num_links, false);
    for (int i = 0; i < num_links; ++i) {
        int next_link = flow_map[i];
        // There is an internal arrival if there is a departure and it is not
        // going into the destination node.
        if (departure[i] && (next_link != -1) ) {
            // The next link should not have been set due to the one-hop
            // interference.
            assert(!return_vec[next_link]);
            return_vec[next_link] = true;
        }
    }
    return return_vec;
}
