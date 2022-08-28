#!/bin/bash
make > /dev/null
echo -e '\n=== Should die at 200-210:'
./philo     1 200 100 101
./tt.sh 1 200 200 101 100
./tt.sh 1 199 200 190 100

echo -e '\n=== Should live:'
./tt.sh 1   4  220 100 100 10
./tt.sh 1   4  410 200 200 10
./tt.sh 1  21  290 100 100 10
./tt.sh 1  50  210 100 100 10
./tt.sh 1 199 2000 600  60 10
