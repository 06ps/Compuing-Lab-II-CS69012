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

Using control connection for sending ftp commands and data connection for file exchange and messages.

Error cases handled:

1. CODEJUD: 1.1	command format: CODEJUD filename(with extension) extension , Eg. CODEJUD add.cpp cpp
	    1.2 file_name having different extension then passed extension
	    1.3 if file_name doesn't exists in server directory
	    1.4 if file doesn't need any input_file
	    1.5 Compile-time error
	    1.6 Runtime-error or TLE
	    1.7 when testcases failed 

2. If file_name not provided by user (In RETR, STOR, DELE)
3. If invalid file_name provided by user (In RETR, STOR, DELE)
4. RETR: If the file already exist in client directory then asking from user whether want to overwrite it or not and doing the operations 		 accordingly
5. If user entered invalid command
6. STOR: If the file already exist in server directory then printing appropriate message to client
7. If file_name provided by user doesn't exists 
8. If server closed by ctrl+c and client try to send query



