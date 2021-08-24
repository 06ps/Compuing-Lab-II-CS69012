""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : mapper1.py
    Date : Feb 22, 2021
    Problem Statement : Find strongly connected network
"""

""" 
    This mapper1.py will take input from 10 day.txt files which contains logs of chat sessions from 1st Feb to 10th Feb 2021. 
    It output the nodes pair having a chat session with count value as 1
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

# variables to keep node pair in sorted order
max_node = None
min_node = None

# taking input coming from standard input (STDIN)
for line in sys.stdin:
    # removing leading and trailing whitespace
    line = line.strip()  
    # storing the nodes in node_arr by splitting the friends node with ","
    node_arr = line.split(",")  
    node1 = int(node_arr[0])
    node2 = int(node_arr[1])    

    if node1 > node2:
        max_node = node1
        min_node = node2

    if node1 < node2:
        max_node = node2
        min_node = node1

    if node1 == node2:
        continue

    print('%s\t%s\t%s' %(min_node, max_node, 1))


