This is Mu-Ti Chung (shortname: mtchung).
The following are the benchmarks of my pieces of codes.

=========================================================================================

Part A. Clock starts from the beginning of the code and ends at the end of the code,
        including reading and writing csv files.

    1. For A and B are 10x10 matrices:
        - matmult.c:            3.339 millisec
        - matmult_npy:          0.747 millisec
        - matmult_pure:         0.423 millisec

    2. For A and B are 100x100 matrices:
        - matmult.c:           18.387 millisec
        - matmult_npy:         61.363 millisec
        - matmult_pure:       113.178 millisec

    
    3. For A and B are 1000x1000 matrices
        - matmult.c:             11.208886 sec
        - matmult_npy.py:         3.067936 sec
        - matmult_pure.py:      190.946851 sec

==========================================================================================

Part B. Clock starts just before the multiplication process and ends as soon as it's 
        finished, i.e., does not include reading and writing csv files.

    1. For A and B are 10x10 matrices:
        - matmult.c:            0.029 millisec
        - matmult_npy:          0.044 millisec
        - matmult_pure:         0.125 millisec

    2. For A and B are 100x100 matrices:
        - matmult.c:            7.282 millisec
        - matmult_npy:          0.126 millisec
        - matmult_pure:       100.103 millisec

    
    3. For A and B are 1000x1000 matrices
        - matmult.c:              9.778988 sec
        - matmult_npy.py:         0.015411 sec
        - matmult_pure.py:      184.812378 sec

==========================================================================================

Comments:

It is obvious to observe that when comparing the speed, npy > c > pure python. C
language is usually known to process faster than other languages such as python. 
Nevertheless, it seems that the speed of matmul() in python has been greatly 
optimized, with its outstanding performance on processing multiplication between
matrices with big sizes. On the other hand, maybe becuase of my poor programming
skill, matmult.c and matmult_pure.py both took a lot of time on calculating
matrices multiplication. There is a significant difference in the 1000x1000 case.