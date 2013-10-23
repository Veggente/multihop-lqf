#!/bin/bash

for number_of_links in 5
do
    for interference_distance in 1
    do
        for iterations in 10000
        do
            for output_period in 1
            do
                for arrival_rate_to_first_node in 0.32
                do
                    filenamestring=n$number_of_links-d$interference_distance-i$iterations-p$output_period-a$arrival_rate_to_first_node
                    ./simulator $number_of_links $interference_distance $iterations $output_period $arrival_rate_to_first_node queues-lqf-$filenamestring.txt queues-bp-$filenamestring.txt
                done
            done
        done
    done
done
