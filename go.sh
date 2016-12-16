#!/bin/sh

if [ $# -lt 1 ];then
    printf "Usage: $0 [Problem number]\n";
    printf "\tSelect No.1 problem: $0 1\n";
    exit 0;
fi

export pro_no=$1
startTime=$((`date +s`))
cd ../../MoonLib
make run
cd -
make run
