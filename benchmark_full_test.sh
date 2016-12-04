#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ];
then
	printf "Usage: $0 OUTPUT_FILE NUMBER_TESTS MAX_SIZE"
	printf "\n\t OUTPUT_FILE is where the data will be stored." 	
	printf "\n\t NUMBER_OF_TESTS is the number of distinct tests that are going to run."
	printf "\n\t MAX_SIZE is the total number of items to be tested (used to generate a vector of NUMBER_OF_TESTS elements from 0 to MAX_SIZE).\n"
	exit 1
fi

data_size=$3
data_sequence=$2
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
