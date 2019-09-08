#!/usr/local/bin/python
import numpy as np
import sys
import csv
import time

def utime_now():
	return int(time.time()*1E6)

class InArgError(Exception):
    def __init__(self, i):
        print 'ERROR: expected positive integer arguments - arg[', i, ']'
        sys.exit()

class MatDimError(Exception):
    def __init__(self, i):
        print 'MatDimError: Matrix dimensions did not match - arg[', i, ']'
        sys.exit()

def check_in_arg(arg, i):
    try:
        in_dim = int(arg)
        if in_dim <= 0:
            raise InArgError(i)
    except ValueError:
        print 'ERROR: expected integer arguments - arg[', i, ']'
        sys.exit()
    return in_dim

def csv2mat(filename, r, c):
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile, quoting = csv.QUOTE_NONNUMERIC)
        row = 0
        out = np.zeros([r,c])
        for line in reader:
            out[row] = line
            row += 1
    return [out, row]

def print2csv(Mat, row, col):
    """
    Print the Mat in CSV format.
    """
    with open('C.csv', 'wb') as csvfile:
        writer = csv.writer(csvfile)
        for r in range(row):
            for c in range(col):
                Mat[r][c] = str(Mat[r][c])
            writer.writerow(Mat[r])
    return

def main():
    # tic
    t_start = utime_now()

    # Reads arguments and checks.
    rowA = check_in_arg(sys.argv[1], 1)
    colA = check_in_arg(sys.argv[2], 2)
    rowB = check_in_arg(sys.argv[3], 3)
    colB = check_in_arg(sys.argv[4], 4)
    
    # Reads CSV files.
    [MatA, rowA] = csv2mat('A.csv', rowA, colA)
    [MatB, rowB] = csv2mat('B.csv', rowB, colB)

    # Calculates multiplication.
    try:
        MatC = np.matmul(MatA, MatB)
    except ValueError:
        print "DimError: Matrix dimensions did not match."
        sys.exit()
    
    # Prints to CSV.
    print2csv(MatC, MatC.shape[0], MatC.shape[1])

    # toc
    t_end = utime_now()
    print 'Time = ', t_end - t_start, ' microseconds.'

if __name__ == '__main__':
    main()