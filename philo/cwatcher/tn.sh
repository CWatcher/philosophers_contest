#!/bin/bash
(($SHLVL == 3)) && echo -e "\n--- philo $2 $3 $4 $5 $6:"
for i in $(seq 1 $1)
do
	./tt.sh $i $2 $3 $4 $5 $6
done
