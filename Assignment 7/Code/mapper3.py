""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : mapper3.py
    Date : Feb 27, 2021
    Problem Statement : Find the number of triangles in the network
"""

""" 
    This mapper.py will take input from network.txt file and friends.txt files. Both files will act as adjacency matrix.
    It will output the key-value pair for matrix- matrix multiplication.
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

# opening the network.txt file  
file_ptr_1 = open("network.txt")
for line in file_ptr_1:
    # removing leading and trailing whitespace
    line = line.strip()  
    # storing the indices in index_arr by splitting the indices value with ","
    index_arr = line.split(',')

    index1 = int(index_arr[0])
    index2 = int(index_arr[1])    

    # for matrix A
    for count1 in range(0,300):
        print('%s\t%s\t%s\t%s' %(index1, count1, index2, 1))
        print('%s\t%s\t%s\t%s' %(index2, count1, index1, 1))

# closing the file
file_ptr_1.close()

# opening the friends.txt file
file_ptr_2 = open("friends.txt")
for line in file_ptr_2:
    line = line.strip()
    index_arr = line.split(',')

    index1 = int(index_arr[0])
    index2 = int(index_arr[1])
    value = int(index_arr[2])

    # for matrix B
    for count2 in range(0,300):
        print('%s\t%s\t%s\t%s' %(count2, index2, index1, value))
        if index1 != index2:
            print('%s\t%s\t%s\t%s' %(count2, index1, index2, value))

# closing the file            
file_ptr_2.close()


