# $1 - output suffix
# $2..$6 - philo args
[ -d log ] || mkdir log
OUTFILE=log/$2_$3_$4_$5_$6.$1.log
./philo $2 $3 $4 $5 $6 > $OUTFILE
echo $(grep died $OUTFILE && echo ';') $(tail -n1 $OUTFILE)
