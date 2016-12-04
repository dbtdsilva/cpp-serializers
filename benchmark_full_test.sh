#!/bin/bash

if [ -z "$1" ]
then
	echo "Usage: $0 output_file"
	exit 1
fi

data_size=700000 	# 70000 * (8 + 8) = 1.2 MB
data_sequence=1000
data_interval=$((data_size/data_sequence))

current_data_request=1
index=0

iterations=100000
while [ $current_data_request -lt $data_size ]
do
	echo ">> Test incoming with a data size of $current_data_request" >> $1
	echo ">> $index of $data_sequence tests" | tee -a $1
	SECONDS=0
	./benchmark $iterations $current_data_request >> $1
	duration=$SECONDS

	if [ $duration -lt 2 ]
	then
		iterations=$((iterations*10))
	fi

	if [ $duration -gt 6 ]
	then
		iterations=$((iterations/5))
	fi

	index=$((index+1))
	current_data_request=$((index*data_interval))
done

echo ">> Tests have finished"
