/*  Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : client.cpp
    Date : Jan 8 , 2021
    Description :The task is to establish a connection between client and server.
                client connects to server sending some arbitrary message and server acknowledges it.

    Compilation Instructions:
    To complie : g++ <source_filename> -o <Any name>
                eg: g++ client.cpp -o client
    To Run : ./<Any name> <Port number>
            eg: ./client 3000
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

using namespace std;


//The driver function in which connection establish between server and client.
int main(int argc, char *argv[])
{
    int sock_fd, num_of_char;
    int port_no;

    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[256];

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
        cout << "*****************************************************************************\n\n";
        cout << "\nClient succesfully get connected to the server !!!\n" <<endl;

    }
    
  
    printf("Send a message to server: ");

    
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);

        num_of_char = write(sock_fd, buffer, strlen(buffer));
        if(num_of_char < 0)
        {
            perror("Error while writing to socket");
            exit(EXIT_FAILURE);
        }

        bzero(buffer, 256);
        num_of_char = read(sock_fd, buffer, 255);
        if(num_of_char < 0)
        {
            perror("Error while reading from socket");
            exit(EXIT_FAILURE);
        }
        printf("Server Message : %s\n\n", buffer);
        cout << "*****************************************************************************\n\n";


    close(sock_fd);
    return 0;
}