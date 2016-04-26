Vigs
====

Quite quick Vigenere Cipher implementation and cryptanalysis tool

vigs encrypts about 26MiBps out of a file on my machine, and the frequency analysis runs at about 32MiBps reading from a file,
as benchmarked against a 64MiB file of /dev/urandom transformed to alphabetic data (essentially an even distribution of alphabetic characters).

Note: if you'd like to run all the tests, throw a large (64MB+) file in `tests/` called `big.in`

it's not git-tracked so that we're not serving giant files everywhere
