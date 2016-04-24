#!/bin/bash

echo -n "Test 3: ftable........."
./ftable tests/3.in tests/3.testout
diff tests/3.testout tests/3.out >/dev/null 2>&1
ret=$?
rm tests/3.testout
if [ $ret -ne 0 ]
then
    echo -e "\033[31mFAIL\033[0m"
    false
else 
    echo -e "\033[32mPASS\033[0m"
    true
fi
