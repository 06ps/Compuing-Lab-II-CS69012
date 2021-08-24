===================================================================================================
Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
Roll No : 20CS60R12
===================================================================================================


Coding Language Used : Python (python3)
Code Run : On Ubuntu 18.04
Status : Code was running fine in my computer system


====================================================================================================

Description:

1. To run file use command: make
2. sort -k 1 -n used in makefile is used to lexicographically sort the data

Query1:	
	mapper.py: Takes the input from network.txt file which consist of friendship relation between two nodes.
		It outputs the nodes of each line with count value as 1 which is going to act as an input to reducer.py file

	reducer.py: Takes the input from mapper.py output in sorted order which consist of node and its count value as 1.
		It outputs the total cost for ad campaign by counting the users which are having atleast 20 friends. The ad cost for each user 			is INR 100 

Query2:
	mapper.py: Takes the input from network.txt file which consist of friendship relation between two nodes. 
		It outputs the nodes of each line with count value as 1 which is going to act as an input to reducer.py file

	reducer.py: Takes input from mapper.py output in sorted order which consist of node and its count value as 1. 
		It outputs the top-10 users which are having highest friends with friends count value.

Query3:
	mapper.py: Takes input from network.txt file which consist of friendship relation between two nodes. 
		It outputs the nodes which are friends with any of the top ten users with count value as 1 which is going to act as an input 			to reducer.py file
	
	reducer.py: Takes input from mapper.py output in sorted order which consist of node and its count value as 1.
		It outputs the nodes which are friends any of the top ten users.

Query4:
	mapper.py: Takes input from network.txt file which consist of friendship relation between two nodes.
		It outputs the nodes which are from US and having friends

	reducer.py: Takes input from mapper.py output in sorted order which consist of node and its count value as 1.
		It outputs the total ad cost when the ad sent to top-10 users with highest number of friends in the US 

