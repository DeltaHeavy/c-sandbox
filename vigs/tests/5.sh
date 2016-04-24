#!/bin/bash

echo -n "Test 5: ftable period.."
./ftable -p 3 tests/5.in tests/5.testout
diff tests/5.testout tests/5.out >/dev/null 2>&1
ret=$?
rm tests/5.testout
if [ $ret -ne 0 ]
then
    echo -e "\033[31mFAIL\033[0m"
    false
else 
    echo -e "\033[32mPASS\033[0m"
    true
fi
