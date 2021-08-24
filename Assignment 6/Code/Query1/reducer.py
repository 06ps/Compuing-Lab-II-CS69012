""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : reducer.py
    Date : Feb 11, 2021
    Problem Statement : Calculate the cost for the ad campaign if floated the ads only for user with atleast 20 friends.

"""

""" 
    This reducer.py will take input from mapper.py output in sorted order which consist of node and its count value as 1. This mapper.py will
    output the total cost for ad campaign by counting the users which are having atleast 20 friends. The ad cost for each is INR 100 
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

#initializing all the variables
current_node_count = 0
current_node = None
node = None

# user_count will keep the count of all users having friends atleast 20
user_count = 0  
total_ad_cost = 0

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
        current_node_count = current_node_count + count
    else:
        if current_node:
            # checking if the node total friend count is atleast 20
            if current_node_count >= 20:
                user_count = user_count + 1
            #print ('%s\t%s' % (current_word, current_count))

        current_node = node
        current_node_count = count


# for the last node 
if current_node:
    if current_node_count >= 20:
        user_count = user_count + 1
    #print ('%s\t%s' % (current_word, current_count))

# calculating the total cost for user having atleast 20 friends
total_cost = user_count * 100

# writing result to standard output (STDOUT)
print("Total number of users with atleast 20 friends: ", user_count)
print("Total ad cost: ", total_cost , " INR")

