""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : mapper.py
    Date : Feb 11, 2021
    Problem Statement : Find out how much have to spend to send ad to the top-10 US users with the highest number of friends in the US.
"""

""" 
    This mapper.py will take input from network.txt file which consist of friendship relation between two nodes. It will
    output the nodes which are from US and having friends
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

# taking input coming from standard input (STDIN) i.e network.txt file
for line in sys.stdin:
    # remove leading and trailing whitespace
    line = line.strip()
    # spliting the line into words
    nodes_arr = line.split(",")
    node1 = int(nodes_arr[0])
    node2 = int(nodes_arr[1])

    if node1 in range(0,1000):
        if node2 in range(0,1000):
            print('%s\t%s' % (node1 , 1))
            print('%s\t%s' % (node2 , 1))
        
        else:
            print('%s\t%s' % (node1, 2))

    else:
        if node2 in range(0,1000):
            print('%s\t%s' % (node2, 2))

"""
If both the nodes are US user then sending both the nodes and keeping the count value as 1,
so that on reducer side it can recognize it as US user. 
If one of the node is US user then sending it and keeping count value as 2,
so that reducer can keep track of total friend count of respective US user

"""

