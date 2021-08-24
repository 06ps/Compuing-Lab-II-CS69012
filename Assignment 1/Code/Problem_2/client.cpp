/*  Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : client.cpp
    Date : Jan 8 , 2021
    Description :The task is to Creates a socket and listens on some specific port to process client
                request. There is a default file present having n lines and the server should be able
                to process EVALUATEX and WRITEX request from the client.

    Compilation Instructions:
    To complie : g++ <source_filename> -o <Any name>
                eg: g++ client.cpp -o client
    To Run : ./<Any name> <localhost> <Port number>
            eg: ./client localhost 3000
*/

//List of header files used
#include<iostream>
#include<stdlib.h>   
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sstream>

using namespace std;


/*The driver function in which connection establish between server and client.
client send command given by user to the server for further processing. 
*/
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

    cout << "\n\n*****************************************************************************\n\n";
    string input;
    cout << " Enter Command: 1. EVALUATEX k \t 2. WRITEX expr\n" <<endl;
    getline(cin, input);

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
    }
    else
    {
        cout << "\nClient succesfully get connected to the server !!!\n" <<endl;
    }
    

    stringstream line(input);
    string str;
    line >> str;     //reading first string before space

    if(str == "EVALUATEX")
    {
        string c_msg;
        string s;
        string new_str = " ";
        while (line >> s)
        {
            new_str = new_str + s;
        }
        
        c_msg = 'E' + new_str;
        strcpy(buffer, c_msg.c_str());
        num_of_char = write(sock_fd, buffer, strlen(buffer)); 
    }
    else if(str == "WRITEX")
    {
        string c_msg;
        string s;
        string new_str;
        while (line >> s)
        {
            new_str = new_str + s;
        }
        
        c_msg = 'W' + new_str;
        strcpy(buffer, c_msg.c_str());
        num_of_char = write(sock_fd, buffer, strlen(buffer));
    }
    else
    {
        cout << "Please Enter a valid command\n\n";
        cout << "*****************************************************************************\n\n";
        exit(1);
    }
    
    bzero(buffer, 256);
    num_of_char = read(sock_fd, buffer, 255);
    if(num_of_char < 0)
    {
        perror("Error while reading from socket");
        exit(EXIT_FAILURE);
    }
    cout <<endl;
    printf("Server Message : %s", buffer);
    cout <<endl;
    cout << "\n*****************************************************************************\n\n";

    close(sock_fd);
    return 0;
}
