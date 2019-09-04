import numpy as np
import sys

def testGen(arg_row, arg_col):
    """
    Generates a normally-distributed random matrix in CSV format.\n
    Gets the matrix dimensions, row and column, from the command line.
    """
    
    # Tests whether the input arguments are integers. If yes, turns them from
    # strings integers; otherwise, raise an ERROR flag and terminates the function.
    try:
        row = int(arg_row)
        col = int(arg_col)
    except ValueError:
        print 'ERROR: expected two integer arguments.'
        return

    # Generates normally-distributed data.
    sol = np.random.standard_normal((row, col))

    # Print the data in CSV format (getting rid of all the line changes and spaces).
    for i in range(row):
        for j in range(col):
            print sol[i,j],; sys.stdout.softspace = False
            if j != col-1:
                print ', ',; sys.stdout.softspace = False
        print '\n',; sys.stdout.softspace = False
    return
    

if __name__ == '__main__':
    # Read command line arguments as function input.
    testGen(sys.argv[1], sys.argv[2])