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

def check_in_arg(arg, i, matdim):
    try:
        in_dim = int(arg)
        if in_dim <= 0:
            raise InArgError(i)
        elif in_dim != matdim:
            raise MatDimError(i)
    except ValueError:
        print 'ERROR: expected integer arguments - arg[', i, ']'
        sys.exit()

def csv2mat(filename):
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile, quoting = csv.QUOTE_NONNUMERIC)
        out = np.array()
        for line in reader:
            
            #out.mat.append(line)
        #out.row = len(out.mat)
        #out.col = len(out.mat[0])
    return out

def matmult(MatA, MatB):
    if MatA.col != MatB.row:
        raise MatDimError

    MatC = Matrix()
    for i in range(MatA.row):
        ls_temp = []
        for j in range(MatB.col):#max 2
            ele = 0
            for k in range(MatA.col):#
                ele += MatA.mat[i][k] * MatB.mat[k][j]
            ls_temp.append(ele)        
        MatC.mat.append(ls_temp)
    MatC.row = MatA.row
    MatC.col = MatB.col

    return MatC

def print2csv(Mat):
    """
    Print the Mat in CSV format.
    """
    with open('C.csv', 'wb') as csvfile:
        writer = csv.writer(csvfile)
        for r in range(Mat.row):
            for c in range(Mat.col):
                Mat.mat[r][c] = str(Mat.mat[r][c])
            writer.writerow(Mat.mat[r])
    return

def main():
    # tic
    t_start = utime_now()
    
    # Reads CSV files.
    MatA = csv2mat('A.csv')
    MatB = csv2mat('B.csv')

    # Check input arguments
    check_in_arg(sys.argv[1], 1, MatA.row)
    check_in_arg(sys.argv[2], 2, MatA.col)
    check_in_arg(sys.argv[3], 3, MatB.row)
    check_in_arg(sys.argv[4], 4, MatB.col)

    # Calculates multiplication.
    MatC = matmult(MatA, MatB)

    # Prints to CSV.
    print2csv(MatC)

    # toc
    t_end = utime_now()
    print 'Time = ', t_end - t_start, ' microseconds.'

if __name__ == '__main__':
    main()