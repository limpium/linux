#!/bin/bash

NUM='^[0-9]+$'
if [ $# -eq 0 ]; then
	echo "no arguments"
	exit
fi

if ! [ $# -eq 2 ]; then
	echo "incorrect number of arguments"
	exit
fi

if ! [[  $1 =~ $NUM ]]; then
	echo "need integer+"
	exit
fi

N=$1
i=1

while [ $i -le $N ]; do
	touch file_$i.txt
        echo $2$i > file_$i.txt
	i=$((i + 1))
done

