""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : mapper.py
    Date : Feb 11, 2021
    Problem Statement : Find the users who have friendship with at least one out of the top-10 users

"""

""" 
    This reducer.py will take input from mapper.py output in sorted order which consist of node and its count value as 1. This mapper.py will
    output the nodes which are friends any of the top ten users.
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

#initializing all the variables
current_node_count = 0
current_node = None
node = None

print("The users who have friendship with at least one out of the top-10 users\n")

# taking input coming from standard input (STDIN) i.e mapper.py output
for line in sys.stdin:
    # removing leading and trailing whitespace
    line = line.strip()

    # parsing the input got from mapper.py
    node, count = line.split('\t')

    # converting count as int
    try:
        count = int(count)
    except ValueError:
        continue

    if current_node == node:
        continue
    else:
        if current_node:
            # writing result to standard output (STDOUT) 
            print ('%s' % (current_node))

        current_node = node

# writing for the last node
print('%s' % (current_node))
    