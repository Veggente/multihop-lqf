//
//  output_vector_to_file.cpp
//  multihop-lqf
//
//  Copyright (c) 2013, 2015 Xiaohan Kang. All rights reserved.
//

#include "output_vector_to_file.h"  // NOLINT
#include <fstream>  // NOLINT
#include <iostream>  // NOLINT

void output_vector_to_file(const Queues &v,  // NOLINT
                           const std::string &filename) {  // NOLINT
    std::ofstream out(filename, std::ofstream::app);
    if (!out) {
        std::cerr << "Error: Could not open file " << filename << "!"
                  << std::endl;
        exit(1);
    }
    for (int i = 0; i < v.size()-1; ++i) {
        out << v[i] << " ";
    }
    out << v.back() << std::endl;
    out.close();
}
