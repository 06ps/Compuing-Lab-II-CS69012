===================================================================================================
Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
Roll No : 20CS60R12
===================================================================================================


Coding Language Used : C++
Complied and Run : On Ubuntu 
Status : Code was running fine in my computer system


====================================================================================================
Commands for command prompt:
++++++ For server.cpp
++++++ Compilation command: g++ server.cpp -o server
++++++ Run command: ./server 8000
====================================================================================================


====================================================================================================
Commands for command prompt:
++++++ For client.cpp
++++++ Compilation command: g++ client.cpp -o client
++++++ Run command: ./client localhost 8000
====================================================================================================

Error cases handled:

1. If file_name not provided by user (In RETR, STOR, DELE)
2. If invalid file_name provided by user (In RETR, STOR, DELE)
3. RETR: If the file already exist in client directory then asking from user whether want to
	 overwrite it or not and doing the operations accordingly
4. If user entered invalid command
5. STOR: If the file already exist in server directory then printing appropriate message to client



