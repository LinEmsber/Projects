#/bin/bash

echo "\n========== gcc -O0 =========="
echo "Peterson's algorithm"
gcc -O0 -Wall -D_P -pthread mutex_lock_test.c && ./a.out
echo "Dekker's algorithm"
gcc -O0 -Wall -D_D -pthread mutex_lock_test.c && ./a.out
echo "pthread_mutex_lock"
gcc -O0 -Wall -D_PTHREAD -pthread mutex_lock_test.c && ./a.out

echo "\n========== clang -O0 =========="
echo "Peterson's algorithm"
clang -O0 -Wall -D_P -pthread mutex_lock_test.c && ./a.out
echo "Dekker's algorithm"
clang -O0 -Wall -D_D -pthread mutex_lock_test.c && ./a.out
echo "pthread_mutex_lock"
clang -O0 -Wall -D_PTHREAD -pthread mutex_lock_test.c && ./a.out

echo "\n========== gcc -Ofast =========="
echo "Peterson's algorithm"
gcc -Ofast -Wall -D_P -pthread mutex_lock_test.c && ./a.out
echo "Dekker's algorithm"
gcc -Ofast -Wall -D_D -pthread mutex_lock_test.c && ./a.out
echo "pthread_mutex_lock"
gcc -Ofast -Wall -D_PTHREAD -pthread mutex_lock_test.c && ./a.out

echo "\n========== clang -Ofast =========="
echo "Peterson's algorithm"
clang -Ofast -Wall -D_P -pthread mutex_lock_test.c && ./a.out
echo "Dekker's algorithm"
clang -Ofast -Wall -D_D -pthread mutex_lock_test.c && ./a.out
echo "pthread_mutex_lock"
clang -Ofast -Wall -D_PTHREAD -pthread mutex_lock_test.c && ./a.out

echo "\n"
