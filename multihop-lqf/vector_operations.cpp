//
//  vector_intersection.cpp
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#include "vector_operations.h"  // NOLINT

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
