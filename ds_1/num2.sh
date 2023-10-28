#!/bin/bash

mkdir WorkDir
touch WorkDir/message.txt
cd WorkDir
echo "$1" >> message.txt
