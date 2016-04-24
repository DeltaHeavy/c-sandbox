#!/bin/bash

echo -n "Test 6: ftable skip...."
./ftable -s 2 tests/6.in tests/6.testout
diff tests/6.testout tests/6.out >/dev/null 2>&1
ret=$?
rm tests/6.testout
if [ $ret -ne 0 ]
then
    echo -e "\033[31mFAIL\033[0m"
    false
else 
    echo -e "\033[32mPASS\033[0m"
    true
fi
