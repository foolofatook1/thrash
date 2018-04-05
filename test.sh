#!/bin/bash

rm test_*.txt

COUNTER=0
MB=500
while [ $COUNTER -lt 20 ];
do
	echo Running $COUNTER MB: $MB
	/usr/bin/time -v ./thrash $MB 2 1 &> test_$COUNTER.txt 
	let COUNTER=COUNTER+1
	let MB=MB+500
done

echo All done
