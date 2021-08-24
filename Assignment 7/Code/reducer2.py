""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : reducer2.py
    Date : Feb 25, 2021
    Problem Statement : Find the number of mutual friends
"""

""" 
    This reducer2.py will take input from mapper2.py output in sorted order which consist key value pair for matrix multiplication
    It will output the number of mutual friends between pair of nodes. 
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

#initializing all the variables
current_row = None
current_col = None
current_val1 = None
current_val2 = None
sum_res = 0

# taking input coming from standard input (STDIN) i.e mapper2.py output
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

    if int(row) < int(col) :
        if current_row == row and current_col == col :
            if current_val1 == val1:
                sum_res = sum_res + 1
            else:
                current_val1 = val1
        else:
            if current_row and current_col :
                # printing only upper traingle except diagonal elements
                print('%s,%s,%s' %(current_row, current_col, sum_res))
                    
            sum_res = 0

            current_row = row
            current_col = col
            current_val1 = val1
            current_val2 = val2


# for the last node 
if current_row and current_col :
    if current_row < current_col:
        print('%s,%s,%s' %(current_row, current_col, sum_res))
