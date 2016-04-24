#!/bin/bash

echo -n "Test 7: ftable p+s....."
./ftable -s 2 -p 3 tests/7.in tests/7.testout
diff tests/7.testout tests/7.out >/dev/null 2>&1
ret=$?
rm tests/7.testout
if [ $ret -ne 0 ]
then
    echo -e "\033[31mFAIL\033[0m"
    false
else 
    echo -e "\033[32mPASS\033[0m"
    true
fi
