/*  Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : server.cpp
    Date : Jan 8 , 2021
    Description :The task is to establish a connection between client and server.
                client connects to server sending some arbitrary message and server acknowledges it.

    Compilation Instructions:
    To complie : g++ <source_filename> -o <Any name>
                eg: g++ server.cpp -o server
    To Run : ./<Any name> <Port number>
            eg: ./server 3000
*/

//List of header files used
#include<iostream>
#include<stdlib.h>  
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fstream>
#include<math.h>

using namespace std;

//The driver function in which connection establish between server and client.
int main(int argc, char* argv[])
{
    int socket_fd, newsocket_fd;
    int port_num;
    socklen_t client_addr_size;
    int num_of_char;
    char buffer[256];

    struct sockaddr_in server_addr, client_addr;
    if(argc < 2)
    {
        cout << ("Error!!! Port number not provided\n");
        exit(1);
    }

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        perror("Error!!!, Socket call failed");
        exit(EXIT_FAILURE);
    }

    bzero((char *) &server_addr, sizeof(server_addr));

    port_num = atoi(argv[1]);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) <0)
    {
        perror("Error!!!, Binding Failed");
        exit(EXIT_FAILURE);
    }    

    while(1)
    {
        listen(socket_fd, 3);

        client_addr_size = sizeof(client_addr);

        newsocket_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_addr_size);

        if(newsocket_fd < 0)
        {
            perror("Error!!! Accept Failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            cout <<"\n\n*************************************************************************\n\n";
            cout << "\nConnection Established with client \n";
        }
        

        bzero(buffer, 256);
        num_of_char = read(newsocket_fd, buffer, 255);
        if(num_of_char < 0)
        {
            perror("Error!!! Reading Failed");
            exit(EXIT_FAILURE);
        }

        printf("Client Message : %s", buffer);

        string output = "Server Received your message";
        bzero(buffer, 256);
        strcpy(buffer, output.c_str());

        num_of_char = write(newsocket_fd, buffer, strlen(buffer));
        if(num_of_char < 0)
        {
            perror("Error while writing to socket");
            exit(EXIT_FAILURE);
        }
        cout << "\n\n*************************************************************************\n\n";
    }
    close(newsocket_fd);
    close(socket_fd);

    return 0;
}
