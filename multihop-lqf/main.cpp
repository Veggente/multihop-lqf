//
//  main.cpp
//  multihop-lqf
//
//  Copyright (c) 2013 Xiaohan Kang. All rights reserved.
//

#include <vector>
#include <string>
#include "line_network_simulator.h"  // NOLINT

int main(int argc, char * const argv[]) {
    int num_links = std::stoi(std::string(argv[1]));
    int interference_distance = std::stoi(std::string(argv[2]));
    int num_iterations = std::stoi(std::string(argv[3]));
    int output_period = std::stoi(std::string(argv[4]));
    double arrival_rate_to_node_one = std::stod(std::string(argv[5]));
    std::string filename_lqf(argv[6]);
    std::string filename_bp(argv[7]);

    // for arrival only to node one
    std::vector<double> arrival_rates(num_links, 0);
    arrival_rates[0] = arrival_rate_to_node_one;

    return line_network_simulator(num_links, interference_distance,
                                  num_iterations, output_period,
                                  arrival_rates, filename_lqf, filename_bp);
}
