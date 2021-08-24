""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : reducer1.py
    Date : Feb 22, 2021
    Problem Statement : Find strongly connected network
"""

""" 
    This reducer1.py will take input from combiner1.py output in sorted order which consist of node pair and count of number of times they chatted.
    It output the node pair who have chatted atleast 30 times in 10 days. The result of reducer1.py will be saved in network.txt file which will
    represent strongly connected network. 
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

#initializing all the variables
current_node_pair_count = 0
current_node_1 = None
current_node_2 = None


# taking input coming from standard input (STDIN)
for line in sys.stdin:
    # removing leading and trailing whitespace
    line = line.strip()

    # parsing the input got from mapper.py
    node_1, node_2, count = line.split('\t')

    # converting count as int
    try:
        count = int(count)
    except ValueError:
        continue

    if current_node_1 == node_1 and current_node_2 == node_2:
        current_node_pair_count = current_node_pair_count + count
    else:
        if current_node_1 and current_node_2 :
            # checking if the node pair chatted for atleast 30 times in 10 days, if yes then printing the node pair
            if(current_node_pair_count >= 30):
                print ('%s,%s' % (current_node_1, current_node_2))            

        current_node_1 = node_1
        current_node_2 = node_2
        current_node_pair_count = count


# for the last node 
if current_node_1 and current_node_2 :
    if(current_node_pair_count >= 30):
        print ('%s,%s' % (current_node_1, current_node_2))
