""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : mapper.py
    Date : Feb 11, 2021
    Problem Statement : Find the users who have friendship with at least one out of the top-10 users

"""

""" 
    This mapper.py will take input from network.txt file which consist of friendship relation between two nodes. It will
    output the nodes which are friends with any of the top ten users with count value as 1 which is going to act as an input to reducer.py file
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

#to keep top 10 user
top_10_user = []

#opening the result.txt of Query2 to get the top 10 users
with open("../Query2/result.txt") as file:
    for _ in range(3):
        #skipping the top3 lines 
        next(file)
    
    for line in file:
        # removing leading and trailing whitespace
        line = line.strip()
        nodes_arr = line.split()
        node = nodes_arr[0]
        # inserting the node in top ten user list
        top_10_user.append(node)


# taking input coming from standard input (STDIN) i.e network.txt file
for line in sys.stdin:
    # removing leading and trailing whitespace
    line = line.strip()  
    # storing the nodes in node_arr by splitting the friends node with ","
    node_arr = line.split(",")  
    node1 = node_arr[0]
    node2 = node_arr[1]    

    """ 
        if a node is friend of any top 10 users then have to send it to reducer.py 
        but if top 10 users are friends among themselves then not sending to reducer.py
    """
    if node1 in top_10_user and node2 in top_10_user:
        continue

    if node1 in top_10_user:
        print('%s\t%s' % (node2, 1))

    if node2 in top_10_user:
        print('%s\t%s' % (node1, 1))

