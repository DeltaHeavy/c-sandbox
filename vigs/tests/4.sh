#!/bin/bash

echo -n "Test 4: ftable pipe...."
./vigs ham tests/4.in | ./ftable > tests/4.testout
diff tests/4.testout tests/4.out >/dev/null 2>&1
ret=$?
rm tests/4.testout
if [ $ret -ne 0 ]
then
    echo -e "\033[31mFAIL\033[0m"
    false
else 
    echo -e "\033[32mPASS\033[0m"
    true
fi
