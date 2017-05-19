"""
Matrix Generation for HPSC
John Dougherty
Haverford College


Start with generating and square matrix of size N consisting of random numbers
where 0 < N.

The matrix will be kept in a file of text, where N is the first line in the file,
and each row of the matrix is a line in the file, and line breaks correspond
to a new row.
"""

from random import *

def GenMatrix(N, filename):
    # N: integer dimension of matrix (N x N); filename: string containing path to data file
    
    assert N > 0
    assert type(N) == type(1)
    assert type(filename) == type("string")
    
    f=open(filename, 'w')
    seed()
    for i in range(N):
        for j in range(N):
            f.write(str(uniform(0, 100)) + "\t")
        f.write("\n")
    f.close()


GenMatrix(100000, "Matrix5.txt")
