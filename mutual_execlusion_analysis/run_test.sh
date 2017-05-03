#/bin/bash

echo "\n================================"
echo "gcc -O0 with pthread_mutex_lock()"
gcc -O0 -Wall -D_P -pthread Dekker_lock.c && ./a.out
echo "gcc -O0 with Dekker's lock"
gcc -O0 -Wall -D_D -pthread Dekker_lock.c && ./a.out

echo "clang -O0 with pthread_mutex_lock()"
clang -O0 -Wall -D_P -pthread Dekker_lock.c && ./a.out
echo "clang -O0 with Dekker's lock"
clang -O0 -Wall -D_D -pthread Dekker_lock.c && ./a.out

echo "\n================================"
echo "gcc -O3 with pthread_mutex_lock()"
gcc -O3 -Wall -D_P -pthread Dekker_lock.c && ./a.out
echo "gcc -O3  with Dekker's lock"
gcc -O3 -Wall -D_D -pthread Dekker_lock.c && ./a.out

echo "clang -O3 with pthread_mutex_lock()"
clang -O3 -Wall -D_P -pthread Dekker_lock.c && ./a.out
echo "clang -O3 with Dekker's lock"
clang -O3 -Wall -D_D -pthread Dekker_lock.c && ./a.out

echo "\n================================"
echo "gcc -Ofast with pthread_mutex_lock()"
gcc -Ofast -Wall -D_P -pthread Dekker_lock.c && ./a.out
echo "gcc -Ofast with Dekker's lock"
gcc -Ofast -Wall -D_D -pthread Dekker_lock.c && ./a.out

echo "clang -Ofast with pthread_mutex_lock()"
clang -Ofast -Wall -D_P -pthread Dekker_lock.c && ./a.out
echo "clang -Ofast with Dekker's lock"
clang -Ofast -Wall -D_D -pthread Dekker_lock.c && ./a.out
