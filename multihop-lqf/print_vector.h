//
//  print_vector.h
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOP_LQF_PRINT_VECTOR_H_
#define MULTIHOP_LQF_PRINT_VECTOR_H_

#include <vector>

template <typename Type>  // print out vector
void print_vector(const std::vector<Type> &v) {
    std::cout << "(";
    typename std::vector<Type>::const_iterator it;
    for (it = v.begin(); it < v.end(); it++) {
        if (it != v.begin()) {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << ")";
}

#endif  // MULTIHOP_LQF_PRINT_VECTOR_H_
