//
//  running_time_check.h
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#ifndef MULTIHOPLQF_RUNNING_TIME_CHECK_H_
#define MULTIHOPLQF_RUNNING_TIME_CHECK_H_

#include <ctime>
#include <iostream>  // NOLINT

std::clock_t start_timer();

double end_timer(std::clock_t start_time);

#endif  // MULTIHOPLQF_RUNNING_TIME_CHECK_H_
