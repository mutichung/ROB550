#!/usr/local/bin/python
import numpy as np
import sys
import csv


def matmult_npy(arg_row1, arg_col1, arg_row2, arg_col2):
    try:
        row1 = int(arg_row1)
        col1 = int(arg_col1)
        row2 = int(arg_row2)
        row2 = int(arg_col2)
    except ValueError:
        print 'ERROR: expected two integer arguments.'
        return
    

    with open('A.csv', 'r') as csvfile:
        reader = csv.reader(csvfile)
        row_count = col_count = 0
        
        #row_count = sum(1 for row in reader)
        #print row_count

        for line in reader:
            row_count += 1
            col_count = len(line)

        print row_count, col_count
    return



if __name__ == '__main__':
    matmult_npy(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])