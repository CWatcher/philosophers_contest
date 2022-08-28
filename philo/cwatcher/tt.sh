# First arg - subsuffix of a filename,
# where output of a philo app is redirected to.
# Next args are passed to a philo app.
#
# Output of the script are "is died" line
# and the last line.

[ -d log ] || mkdir log
OUTFILE=log/$2_$3_$4_$5_$6.$1.log
./philo $2 $3 $4 $5 $6 > $OUTFILE

DEATH_MESSAGE=$(grep d $OUTFILE)
LAST_MESSAGE=$(tail -n1 $OUTFILE)

if [[ $DEATH_MESSAGE == "" || $DEATH_MESSAGE == $LAST_MESSAGE ]]; then
	DEATH_MESSAGE=""
else
	DEATH_MESSAGE+="; "
fi
echo "$DEATH_MESSAGE$LAST_MESSAGE"
