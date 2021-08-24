===================================================================================================
Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
Roll No : 20CS60R12
===================================================================================================


Coding Language Used : Python (python3)
Code Run : On Ubuntu 20.04.2 LTS
Status : Code was running fine in my computer system


====================================================================================================

Description:

1. To run files use command: make
2. sort -k 1 -k 2 -n and sort -k 1 -k 2 -k 3 -n used in makefile to lexicographically sort the data

Query1:	
	mapper1.py: Takes the input from 10 day.txt files which contains logs of chat sessions from 1st Feb to 10th Feb 2021. 
		It output the nodes pair having a chat session with count value as 1
	
	combiner1.py: Takes input from mapper1.py output in sorted order which consist of node pair having a chat session.
		It output the number of times two node pairs chatted. Act as mini reducer.

	reducer1.py: Takes input from combiner1.py output in sorted order which consist of node pair and count of number of times they 			chatted. It output the node pair who have chatted atleast 30 times in 10 days. The result of reducer1.py will be saved in 			network.txt file which will represent strongly connected network.

Query2:
	mapper2.py: Takes input from network.txt file which act as a adjacency matrix i.e it is having those row-col indexes whose 		corresponding value is 1. It output the key value pair for matrix-matrix multiplication.

	reducer2.py: Takes input from mapper2.py output in sorted order which consist key value pair for matrix multiplication.
		It output the number of mutual friends between pair of nodes. The result of reducer2.py will be saved in friends.txt.

Query3:
	mapper3.py: Takes input from network.txt file and friends.txt files. Both files will act as adjacency matrix.
		It will output the key-value pair for matrix- matrix multiplication.
	
	reducer3.py: Takes input from mapper3.py output in sorted order which consist of key value pair for matrix multiplicaton.
		It will output the number of triangles passes through each nodes. The result of reducer3.py will be saved in triangles.txt.


