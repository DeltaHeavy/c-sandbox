#!/bin/bash

if [ -f tests/big.in ]; then
    size=$(du -hs tests/big.in | awk '{ print $1 }')
    echo -n "Test 9: ftable $size....."
    /usr/bin/time -f " (time elapsed: %es)" ./ftable tests/big.in >/dev/null 2>big.out
    ret=$?
    if [ $ret -ne 0 ]
    then 
        echo -ne "\033[31mFAIL\033[0m"
        false
    else
        echo -ne "\033[32mPASS\033[0m"
        true
    fi
    cat big.out
    rm big.out
else
    echo "Skipping test 9: no tests/big.in"
fi
