#/bin/bash

echo "\n================================"
echo "gcc -O0 with Peterson's algorithm"
gcc -O0 -Wall -D_P -pthread mutex_lock_test.c && ./a.out
echo "gcc -O0 with Dekker's algorithm"
gcc -O0 -Wall -D_D -pthread mutex_lock_test.c && ./a.out

echo "clang -O0 with Peterson's algorithm"
clang -O0 -Wall -D_P -pthread mutex_lock_test.c && ./a.out
echo "clang -O0 with Dekker's algorithm"
clang -O0 -Wall -D_D -pthread mutex_lock_test.c && ./a.out

echo "\n================================"
echo "gcc with Peterson's algorithm"
gcc -Ofast -Wall -D_P -pthread mutex_lock_test.c && ./a.out
echo "gcc with Dekker's algorithm"
gcc -Ofast -Wall -D_D -pthread mutex_lock_test.c && ./a.out

echo "clang with Peterson's algorithm"
clang -Ofast -Wall -D_P -pthread mutex_lock_test.c && ./a.out
echo "clang with Dekker's algorithm"
clang -Ofast -Wall -D_D -pthread mutex_lock_test.c && ./a.out

echo "\n"
