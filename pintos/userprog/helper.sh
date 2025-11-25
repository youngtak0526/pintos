#!/bin/bash
set -e

if [ -z "$1" ]; then
    echo "Usage: ./helper.sh <program>"
    exit 1
fi
make
cd build || { echo "build don't exist"; exit 1; }
pintos-mkdisk filesys.dsk 2
pintos --fs-disk=filesys.dsk -- -f -q
pintos --fs-disk=filesys.dsk -p tests/userprog/"$1" -- -q run "$1"