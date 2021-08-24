
""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : mapper.py
    Date : Feb 11, 2021
    Problem Statement : Find the top-10 users (node-ids) with the highest number of friends

"""

""" 
    This mapper.py will take input from network.txt file which consist of friendship relation between two nodes. It will
    output the nodes of each line with count value as 1 which is going to act as an input to reducer.py file
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

# taking input coming from standard input (STDIN)
for line in sys.stdin:
    # removing leading and trailing whitespace
    line = line.strip()  
    # storing the nodes in node_arr by splitting the friends node with ","
    node_arr = line.split(",")             

    for node in node_arr:
        # writing the results to standard output (STDOUT)
        print ( '%s\t%s' % (node, 1))       

