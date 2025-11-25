#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: ./helper.sh <program>"
    exit 1
fi

args=("$@")

for ((i=0;i<$#;i++))
do
    backtrace "${args[i]}"
done