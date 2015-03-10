#!/bin/bash

for iterations in 1000000
do
    for output_period in 100000
    do
        for arrival_ratio in 0.255 0.26 0.265
        do
            filenamestring=i$iterations-p$output_period-a$arrival_ratio
            ./simulator $iterations $output_period $arrival_ratio queues-lqf-$filenamestring.txt queues-bp-$filenamestring.txt
        done
    done
done
