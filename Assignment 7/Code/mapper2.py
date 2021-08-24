""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : mapper2.py
    Date : Feb 25, 2021
    Problem Statement : Find the number of mutual friends
"""

""" 
    This mapper2.py will take input from network.txt file which act as a adjacency matrix i.e it is having those row-col indexes whose corresponding value is 1
    It will output the key value pair for matrix-matrix multiplication.
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

# taking input coming from standard input (STDIN) i.e network.txt file
for line in sys.stdin:
    # removing leading and trailing whitespace
    line = line.strip()  
    # storing the indices in index_arr by splitting the indices value with ","
    index_arr = line.split(',')

    index1 = int(index_arr[0])
    index2 = int(index_arr[1])    

    # printing for 300 times because 300 x 300 matrix size
    for count1 in range(0,300):
        # for matrix A
        print('%s\t%s\t%s\t%s' %(index1, count1, index2, 1))
        print('%s\t%s\t%s\t%s' %(index2, count1, index1, 1))
        # for another matrix which is also A
        print('%s\t%s\t%s\t%s' %(count1, index2, index1, 1))
        print('%s\t%s\t%s\t%s' %(count1, index1, index2, 1))



