""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : reducer3.py
    Date : Feb 27, 2021
    Problem Statement : Find the number of triangles in the network: 
"""

""" 
    This reducer3.py will take input from mapper3.py output in sorted order which consist of key value pair for matrix multiplicaton.
    It will output the number of triangles passes through each nodes. 
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

#initializing all the variables
current_row = None
current_col = None
prev_val1 = None
prev_val2 = None
sum_res = 0
product = 1

# taking input coming from standard input (STDIN) i.e mapper3.py output
for line in sys.stdin:
    # removing leading and trailing whitespace
    line = line.strip()

    # parsing the input got from mapper.py
    row, col, val1, val2 = line.split('\t')

    # converting value as int
    try:
        val2 = int(val2)
        val1 = int(val1)
    except ValueError:
        continue

    if int(row) == int(col):
        if current_row == row and current_col == col :
            if prev_val1 == val1:
                product = prev_val2 * val2
                sum_res = sum_res + product

            else:
                product = 1
                prev_val1 = val1
                prev_val2 = val2
        else:
            if current_row and current_col :
                # printing the node and number of triangles passes through it, dividing the result by 2 because its a directed graph
                print('%s,%s' %(current_row, int(sum_res/2)))           
            sum_res = 0
            product = 1

            current_row = row
            current_col = col
            prev_val1 = val1
            prev_val2 = val2


# for the last node 
if current_row and current_col :
    if current_row == current_col:
        print('%s,%s' %(current_row, int(sum_res/2)))
