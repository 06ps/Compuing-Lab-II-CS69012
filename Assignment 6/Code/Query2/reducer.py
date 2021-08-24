""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : reducer.py
    Date : Feb 11, 2021
    Problem Statement : Find the top-10 users (node-ids) with the highest number of friends

"""

""" 
    This reducer.py will take input from mapper.py output in sorted order which consist of node and its count value as 1. This mapper.py will
    output the top-10 users which are having highest friends with friends count value.
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

#initializing all the variables
current_node_count = 0
current_node = None
node = None

# defining a dictionary to keep top 10 users
top_10_user = {}
# to store key having minimum number of friends among all the dictonary elements
min_value_key = 0
min_value = 0
# to keep dictonary size of 10
count_10 = 0


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
            """ 
            intial ten nodes are stored in dictonary with their number of friends,
            11th node onwards, finding the node with min number of friends say it as 
            min_value and comparing it with the current node friend count, if the current node 
            friend count is greater than the min_value then replacing that key:value pair 
            with current node key:value pair

            """ 
            if(count_10 < 10):
                top_10_user[current_node] = current_node_count
                count_10 =  count_10 + 1
            else:
                min_value_key = min(top_10_user, key=top_10_user.get)
                min_value = top_10_user.get(min_value_key)
                if(min_value < current_node_count):
                    top_10_user.pop(min_value_key)
                    top_10_user[current_node] = current_node_count
            #print ('%s\t%s' % (current_word, current_count))

        current_node = node
        current_node_count = count


# comparing the friend_count_value of the last node with dict values
if current_node:
    min_value_key = min(top_10_user, key=top_10_user.get)
    min_value = top_10_user.get(min_value_key)
    if(min_value < current_node_count):
        top_10_user.pop(min_value_key)
        top_10_user[current_node] = current_node_count
    #print ('%s\t%s' % (current_word, current_count))

# sorting the key:value pair in decreasing order of number of total friends
sorted_top_10_user = {}
sorted_keys = sorted(top_10_user, key = top_10_user.get, reverse=True)   

for i in sorted_keys:
    sorted_top_10_user[i] = top_10_user[i]

# writing the top-10 user and its total friend count to standard output (STDOUT)
print("Top 10 Users are\n")
print("User\t\tNumber of Friends")

for i in sorted_top_10_user:
    print(i, "\t\t" , sorted_top_10_user[i])

