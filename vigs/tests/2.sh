#!/bin/bash

echo -n "Test 2: vigs decrypt..."
./vigs -d ham tests/2.in tests/2.testout
diff tests/2.testout tests/2.out >/dev/null 2>&1
ret=$?
rm tests/2.testout
if [ $ret -ne 0 ]
then 
    echo -e "\033[31mFAIL\033[0m"
    false
else
    echo -e "\033[32mPASS\033[0m"
    true
fi
