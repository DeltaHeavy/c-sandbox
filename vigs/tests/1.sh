#!/bin/bash

echo -n "Test 1: Encrypt..."
./vigs ham tests/1.in tests/1.testout
diff tests/1.testout tests/1.out >/dev/null 2>&1
ret=$?
rm tests/1.testout
if [ $ret -ne 0 ]
then
    echo -e "\033[31mFAIL\033[0m"
    false
else 
    echo -e "\033[32mPASS\033[0m"
    true
fi
