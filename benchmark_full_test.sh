#!/bin/bash

data_size=70000 	# 70000 * (8 + 8) = 1.2 MB
data_sequence=1000
data_interval=$((data_size/data_sequence))

current_data_request=1
index=0

iterations=1000
while [ $current_data_request -lt $data_size ]
do
	printf "\n\n>> Test incoming with a data size of " $current_data_request
	SECONDS=0
	./benchmark $iterations $current_data_request
	duration=$SECONDS

	if [ $duration -lt 2 ]
	then
		iterations=$((iterations*10))
	fi

	if [ $duration -gt 10 ]
	then
		iterations=$((iterations/10))
	fi

	index=$((index+1))
	current_data_request=$((index*data_interval))
done
