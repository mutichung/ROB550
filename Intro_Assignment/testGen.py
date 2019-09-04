import numpy as np
import sys

def testGen(arg_row, arg_col):
    try:
        row = int(arg_row)
        col = int(arg_col)
    except ValueError:
        print 'ERROR: expected two integer arguments.'
        return

    sol = np.random.standard_normal((row, col))
    for i in range(row):
        for j in range(col):
            print sol[i,j],; sys.stdout.softspace = False
            if j != col-1:
                print ', ',; sys.stdout.softspace = False
        print '\n',; sys.stdout.softspace = False
    

if __name__ == '__main__':
    testGen(sys.argv[1], sys.argv[2])