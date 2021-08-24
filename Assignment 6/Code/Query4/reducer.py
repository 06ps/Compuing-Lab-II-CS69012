""" 
    Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : mapper.py
    Date : Feb 11, 2021
    Problem Statement : Find out how much have to spend to send ad to the top-10 US users with the highest number of friends in the US.
"""

""" 
    This reducer.py will take input from mapper.py output in sorted order which consist of node and its count value as 1. This mapper.py will
    output the total ad cost when the ad sent to top-10 users with highest number of friends in the US 
"""

# Provides functions and variables which are used to manipulate different parts of the Python Runtime Environment
import sys

#initializing all the variables
current_node = None
total_friend_count = 0
us_friend_count = 0

# defining two dictionary of size 10 to keep US_friend_count and Total_friend count
us_friend = {}
total_friend = {}
# to keep dictonary size of 10
count_10 = 0

total_cost = 0

# taking input coming from standard input (STDIN) i.e mapper.py output
for line in sys.stdin:
    # removing leading and trailing whitespace
    line = line.strip()

    # parsing the input got from mapper.py
    node, count = line.split("\t")

    # converting count as int
    try:
        count = int(count)
    except ValueError:
        continue

    if current_node == node:
        # count = 1 indicate US user, count = 2 indicate other than US user
        # if count is 1 then increment both the US and total_friend_count, if count is 2 then increment only total_friend count
        if count == 1:
            total_friend_count = total_friend_count + 1
            us_friend_count = us_friend_count + 1
        
        if count == 2:
            total_friend_count = total_friend_count + 1

    else:
        if current_node:
            """ 
                intial ten nodes are stored in both the dictonary(us_friend and total_friend) with their
                US_friend count and total_friend_count as value and key will be the current word.
                11th nodes onward, find the node with min number of us_friend_count say 
                it as min_value and comparing it with the current node us_friend_count, if the current
                node us_friend_count is greater than the min_value then replacing that key:value pair 
                with current node key:value pair in both the dictonaries

            """ 
            if(count_10 < 10): 
                us_friend[current_node] = us_friend_count
                total_friend[current_node] = total_friend_count
                count_10 =  count_10 + 1
            else:
                min_value = min(us_friend.values())
                min_value_key_list = []

                for i in us_friend:
                    if us_friend[i] == min_value:
                        min_value_key_list.append(i)


                if(min_value < us_friend_count):
                    max_x = 0
                    key_x = None
                    for i in min_value_key_list:
                        if(total_friend[i] > max_x):
                            max_x = total_friend[i]
                            key_x = i
      
                    us_friend.pop(key_x)
                    total_friend.pop(key_x)
                    us_friend[current_node] = us_friend_count
                    total_friend[current_node] = total_friend_count

                
                if(min_value == us_friend_count):
                    max_x = 0
                    key_x = None
                    for i in min_value_key_list:
                        if(total_friend[i] > max_x):
                            max_x = total_friend[i]
                            key_x = i
                    
                    if(max_x > total_friend_count):
                        us_friend.pop(key_x)
                        total_friend.pop(key_x)
                        us_friend[current_node] = us_friend_count
                        total_friend[current_node] = total_friend_count

        current_node = node
        if count == 1:
            total_friend_count = 1
            us_friend_count = 1
    
        if count == 2:
            total_friend_count = 1
            us_friend_count = 0
                
# comparing the us_friend_count_value of the last node with dict values
if current_node:
    min_value = min(us_friend.values())
    min_value_key_list = []

    for i in us_friend:
        if us_friend[i] == min_value:
            min_value_key_list.append(i)

    if(min_value <= us_friend_count):
        max_x = 0
        key_x = None
        for i in min_value_key_list:
            if(total_friend[i] > max_x):
                max_x = total_friend[i]
                key_x = i

        us_friend.pop(key_x)
        total_friend.pop(key_x)
        us_friend[current_node] = us_friend_count
        total_friend[current_node] = total_friend_count

    if(min_value == us_friend_count):
        max_x = 0
        key_x = None
        for i in min_value_key_list:
            if(total_friend[i] > max_x):
                max_x = total_friend[i]
                key_x = i
        
        if(max_x > total_friend_count):
            us_friend.pop(key_x)
            total_friend.pop(key_x)
            us_friend[current_node] = us_friend_count
            total_friend[current_node] = total_friend_count


# writing the top-10 user, its total_us_friend_count and total_friend_count to standard output (STDOUT)
print("The top 10 users with highest number of US users are\n")
print("US User : Total US friends : Total Friends")

for i in us_friend:
    total_cost = total_cost + total_friend[i]*10
    print(i," : " , us_friend[i], " : ",  total_friend[i])

# writing the total cost to standard output (STDOUT)
print("\n")
print('Total ad cost: ', total_cost, " INR")

