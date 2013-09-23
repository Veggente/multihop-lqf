//
//  running_time_check.cpp
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#include "running_time_check.h"  // NOLINT

std::clock_t start_timer() {
    std::cout << "Timer started!" << std::endl;
    return std::clock();
}

double end_timer(std::clock_t start_time) {
    std::clock_t end_time = std::clock();
    double elapsed_time_in_ms = 1000.0*(end_time-start_time)/CLOCKS_PER_SEC;
    std::cout << "Timer ended! The elapsed time is " << elapsed_time_in_ms
              << " ms" << std::endl;
    return elapsed_time_in_ms;
}
