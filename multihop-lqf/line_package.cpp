//
//  line_package.cpp
//  multihop-lqf
//
//  Copyright (c) 2015 Xiaohan Kang. All rights reserved.
//

#include "line_package.h"
#include <string>
#include <vector>
#include "line_network_simulator.h"

int line_net_package(int argc, char * const argv[]) {
    int num_links = std::stoi(std::string(argv[1]));
    int interference_distance = std::stoi(std::string(argv[2]));
    int num_iterations = std::stoi(std::string(argv[3]));
    int output_period = std::stoi(std::string(argv[4]));
    double arrival_rate_to_node_one = std::stod(std::string(argv[5]));
    std::string filename_lqf(argv[6]);
    std::string filename_bp(argv[7]);
    // Packets only arrive on node one.
    std::vector<double> arrival_rates(num_links, 0);
    arrival_rates[0] = arrival_rate_to_node_one;
    return line_network_simulator(num_links, interference_distance,
                                  num_iterations, output_period, arrival_rates,
                                  filename_lqf, filename_bp);
}
