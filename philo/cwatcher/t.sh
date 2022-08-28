#!/bin/bash
make > /dev/null
echo -e '\n=== Should die at 200-210:'
./philo     1 200 100 101
./tt.sh 1 200 200 101 100
./tt.sh 1 199 200 190 100

echo -e '\n=== Should live:'
./tt.sh 1  4 220 100 100 10
./tt.sh 1  5 400 100 100 10
./tt.sh 1 80 220 100 100 10
if [ "$(uname)" = "Darwin" ]; then
	./tt.sh 1  5 260 100 100 10
	./tt.sh 1 81 230 100 100 10
else
	./tt.sh 1  5 520 200 200 10
	./tt.sh 1 81 460 200 200 10
fi

echo -e '\n=== Survival test:'
if [ "$(uname)" = "Darwin" ]; then
	./tn.sh 5   2 200 100 100 10
	./tn.sh 5  20 200 100 100 10
	./tn.sh 5 200 203 100 100 10
	./tn.sh 5 200 202 100 100 10
	./tn.sh 5 199 203 100 100 10
	./tn.sh 5 199 202 100 100 10
else
	./tn.sh 5   2 210 100 100 10
	./tn.sh 5  20 220 100 100 10
	./tn.sh 5 200 240 100 100 10
	./tn.sh 5 200 220 100 100 10
	./tn.sh 5 199 920 400 400 10
	./tn.sh 5 199 690 300 300 10
fi
