# Unit stride

## Introduction

In computer programming, the stride of an array is the number of locations in memory between beginnings of successive array elements, measured in bytes or in units of the size of the array's elements.

An array with stride of exactly the same size as the size of each of its elements is contiguous in memory. Such arrays are sometimes said to have unit stride. Unit stride arrays are sometimes more efficient than non-unit stride arrays, but non-unit stride arrays can be more efficient for 2D or multi-dimensional arrays, depending on the effects of caching and the access patterns used. This can be attributed to the Principle of Locality, specifically spatial locality.

## Row Major

```bash
$ gcc -D_I matrix_unit_stride.c && valgrind --tool=cachegrind ./a.out
```


        ==11056== Cachegrind, a cache and branch-prediction profiler
        ==11056== Copyright (C) 2002-2015, and GNU GPL'd, by Nicholas Nethercote et al.
        ==11056== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
        ==11056== Command: ./a.out
        ==11056==
        --11056-- warning: L3 cache found, using its data for the LL simulation.
        ==11056==
        ==11056== I   refs:      11,007,098,753
        ==11056== I1  misses:               760
        ==11056== LLi misses:               751
        ==11056== I1  miss rate:           0.00%
        ==11056== LLi miss rate:           0.00%
        ==11056==
        ==11056== D   refs:       6,004,038,542  (5,003,026,885 rd   + 1,001,011,657 wr)
        ==11056== D1  misses:        62,501,776  (        1,274 rd   +    62,500,502 wr)
        ==11056== LLd misses:        62,501,600  (        1,121 rd   +    62,500,479 wr)
        ==11056== D1  miss rate:            1.0% (          0.0%     +           6.2%  )
        ==11056== LLd miss rate:            1.0% (          0.0%     +           6.2%  )
        ==11056==
        ==11056== LL refs:           62,502,536  (        2,034 rd   +    62,500,502 wr)
        ==11056== LL misses:         62,502,351  (        1,872 rd   +    62,500,479 wr)
        ==11056== LL miss rate:             0.4% (          0.0%     +           6.2%  )

## Column Major

```bash
$ gcc -D_J matrix_unit_stride.c && valgrind --tool=cachegrind ./a.out
```

        ==11176== Cachegrind, a cache and branch-prediction profiler
        ==11176== Copyright (C) 2002-2015, and GNU GPL'd, by Nicholas Nethercote et al.
        ==11176== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
        ==11176== Command: ./a.out
        ==11176==
        --11176-- warning: L3 cache found, using its data for the LL simulation.
        ==11176==
        ==11176== I   refs:      11,007,098,753
        ==11176== I1  misses:               760
        ==11176== LLi misses:               751
        ==11176== I1  miss rate:           0.00%
        ==11176== LLi miss rate:           0.00%
        ==11176==
        ==11176== D   refs:       6,004,038,542  (5,003,026,885 rd   + 1,001,011,657 wr)
        ==11176== D1  misses:       999,997,781  (        1,274 rd   +   999,996,507 wr)
        ==11176== LLd misses:        62,502,551  (        1,121 rd   +    62,501,430 wr)
        ==11176== D1  miss rate:           16.7% (          0.0%     +          99.9%  )
        ==11176== LLd miss rate:            1.0% (          0.0%     +           6.2%  )
        ==11176==
        ==11176== LL refs:          999,998,541  (        2,034 rd   +   999,996,507 wr)
        ==11176== LL misses:         62,503,302  (        1,872 rd   +    62,501,430 wr)
        ==11176== LL miss rate:             0.4% (          0.0%     +           6.2%  )


## Conclusion

The D1 miss rate almost 100% when the matrix is computed in column major.

## References:
- [Stride of an array](https://en.wikipedia.org/wiki/Stride_of_an_array)
- [Accessing elements of a matrix row-wise versus column-wise](https://stackoverflow.com/questions/4716125/accessing-elements-of-a-matrix-row-wise-versus-column-wise)
