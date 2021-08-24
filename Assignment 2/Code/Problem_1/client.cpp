/*  Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : client.cpp
    Date : Jan 15 , 2021
    Description : The task is to create a server and listen at some specific port to process client request.
                The server program will “fork” a process for every new client it receives, such that each child
                process is responsible for handling the request of one client

    Compilation Instructions:
    To complie : g++ <source_filename> -o <Any name>
                eg: g++ client.cpp -o client
    To Run : ./<Any name> <localhost> <Port number>
            eg: ./client localhost 3000
*/

//List of Header files used
#include<iostream>
#include<stdlib.h>   //for exit()
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

using namespace std;


/*The driver function in which connection establish between server and client.
Client send its request to server to perform infix to postfix conversion and postfix evaluation.
In return, server reply it with appopriate results
*/
int main(int argc, char *argv[])
{
    int sock_fd, num_of_char;
    int port_no;

    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[1024];

    if(argc < 3)
    {
        fprintf(stderr, "%s hostname or port missing", argv[0]);
        cout<<endl;
        exit(0);
    }

    port_no = atoi(argv[2]);
    
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0)
    {
        perror("Error!!!, Socket call failed");
        exit(EXIT_FAILURE);
    }
    

    server = gethostbyname("localhost");
    if(server == NULL)
    {
        fprintf(stderr, "Error!!!, no such host exist\n");
        exit(0);
    }

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port_no);

    if(connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error while connecting");
        exit(EXIT_FAILURE);
    }else
    {
        cout << "\nConnected to Server\n" <<endl;
        cout << "Enter 'E' to Exit \n";
    }
    
    while(1)
    {   
        string input;
        cout << "\nPlease enter the message to the server: ";
        getline(cin, input);

        bzero(buffer, 1024);
        strcpy(buffer, input.c_str());
 
        num_of_char = write(sock_fd, buffer, strlen(buffer));
        if(num_of_char < 0)
        {
            perror("Error while writing to socket");
            exit(EXIT_FAILURE);
        }

        if(input == "E")
            break;

        bzero(buffer, 1024);
        num_of_char = read(sock_fd, buffer, 1023);
        if(num_of_char < 0)
        {
            perror("Error while reading from socket");
            exit(EXIT_FAILURE);
        }
        printf("Server replied : %s\n", buffer);

    }
    close(sock_fd);
    return 0;
}