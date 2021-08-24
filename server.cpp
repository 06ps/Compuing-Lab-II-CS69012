/*  Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : server.cpp
    Date : Jan 15 , 2021
    Description : The task is to create a server and listen at some specific port to process client request.
                The server program will “fork” a process for every new client it receives, such that each child
                process is responsible for handling the request of one client

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
#include<sys/types.h>
#include<netinet/in.h>
#include<fstream>
#include<math.h>
#include<arpa/inet.h>
#include<ctime>

#define MAX 100

using namespace std;

struct optr_stack                       //For operator stack during postfix conversion
{
    int top;
    char op[MAX];
};

struct value                            //For value stack during postfix evaluation
{
    int top;
    string data[MAX];
};


/*  Function Name : push()
    Input :         optr_stack reference, char
    Output:         push op
    Description:    push operator to optr_stack. 
*/
void push(struct optr_stack *stack, char op)
{
    if(stack->top == MAX-1)
    {
        cout << "Stack Overflow\n";
        exit(1);
    }
    else
    {
        stack->op[++(stack->top)] = op;
    }    
}


/*  Function Name : pop()
    Input :         optr_stack reference
    Output:         pop element
    Description:    pop element from optr_stack. 
*/
char pop(struct optr_stack *stack)
{
    return stack->op[(stack->top)--];
}


/*  Function Name : stack_top()
    Input :         optr_stack reference
    Output:         char
    Description:    Returns optr_stack top element. 
*/
char stack_top(struct optr_stack *stack)
{
    return stack->op[(stack->top)];
}


/*  Function Name : push_value()
    Input :         value_stack reference, string
    Output:         push string
    Description:    push element to value_stack. 
*/
void push_value(struct value *val_stack, string val)
{
    if(val_stack->top == MAX -1)
    {
        cout << "Stack Overflow\n";
        exit(1);
    }
    else
    {
        val_stack->data[++(val_stack->top)] = val;
    }
}


/*  Function Name : pop_value()
    Input :         value_stack reference
    Output:         pop element
    Description:    pop element from value_stack and return popped element. 
*/
double pop_value(struct value *val_stack)
{
    if(val_stack->top == -1)
    {
        return 0;
    }
    else
    {
        double val = stod(val_stack->data[(val_stack->top)--]);
        return val;
    }   
}


/*  Function Name : check_precedence()
    Input :         optr
    Output:         0 or 1 or 2 or 3 or 4
    Description:    This function computes precendence order of operators and return appropriate value. 
*/
int check_precedence(char op)
{
    if(op == '+' || op == '-')
        return 1;
    if(op == '*' || op == '/' || op == '%')
        return 2;
    if(op == '#')
        return 3;
    if(op == '^')
        return 4;
}


/*  Function Name : infix_to_postfix()
    Input :         string
    Output:         string
    Description:    This function will calculate postfix expression for the given infix expression. 
*/
string infix_to_postfix(string str)
{
    optr_stack optr_stack;
    optr_stack.top = -1;
    string postfix;

    for(int i=0; i<str.length(); i++)
    {
        if(str[i] == ' ' || str[i] == '\t')
            continue;
        
        else if(str[i] == '(')
        {
            push(&optr_stack, str[i]);
        }
        
        else if(isdigit(str[i]) || str[i] == '.')
        {
            int count = 0;
            if(str[i] == '.')
            {
                count++;
                postfix = postfix + str[i];
                i++;
            }

            while(i<str.length() && ((isdigit(str[i])) || str[i] == '.'))
            {
                if(str[i] == '.')
                    count++;

                if(count < 2)
                {
                    postfix = postfix + str[i];
                    i++;
                }
                else
                {
                    postfix = "I";
                    return postfix;
                }
                
            }
            postfix = postfix + " ";
            i--;
        }
        else if(str[i] == ')')
        {
            if(optr_stack.top == -1)
            {
                postfix = "I";
                return postfix;
            }
            while(stack_top(&optr_stack) != '(')
            {
                char ch = pop(&optr_stack);
                postfix = postfix + ch;
                postfix = postfix + ' ';
            }
            pop(&optr_stack);
        }
        else 
        {
            
            while((optr_stack.top != -1) && (stack_top(&optr_stack) != '(') && (check_precedence(str[i]) <= check_precedence(stack_top(&optr_stack))) && !(stack_top(&optr_stack) == '^' && str[i] == '^'))
            {
                char ch = pop(&optr_stack);
                postfix = postfix + ch;
                postfix = postfix + ' ';
            }
            push(&optr_stack, str[i]); 
        }      
    }

    while(optr_stack.top != -1)
    {
        char ch = pop(&optr_stack);
        postfix = postfix + ch;
        postfix = postfix + ' ';
    }

    if(postfix.length() == 0)
    {
        postfix = "I";
        return postfix;
    }
    return postfix;
}


/*  Function Name : calculate()
    Input :         2 double type values and 1 char type value
    Output:         value of types double
    Description:    Returns value after applying given mathematical operation between two values. 
*/
double calculate(double a, double b, char op)
{
    switch(op)
    {
        case '+':   return a+b;
        case '-':   return a-b;
        case '*':   return a*b;
        case '/':   return a/b;
        case '^':   return pow(a,b);
        case '%':   return fmod(a,b);
        case '#':   return (a+b)*-1;
    }
}


/*  Function Name : postfix_Eva()
    Input :         string type expression
    Output:         string type result
    Description:    This function will Evaluate given postfix expression and return its result. 
*/
string postfix_Eva(string exp)
{
    value val_stack;
    val_stack.top = -1;
    double val1, val2, res;

    for(int i=0; i<exp.length(); i++)
    {
        if(exp[i] == ' ' || exp[i] == '\t')
            continue;
        else if(isdigit(exp[i]) || exp[i] == '.')
        {
            string num;
            while(exp[i]!= ' ' && (isdigit(exp[i]) || exp[i] == '.'))
            {
                num  = num + exp[i];
                i++;
            }
            //cout << num << "me ";
            //string s = exp[i];
            push_value(&val_stack, num);
        }
        else if(exp[i] == '#')
        {
            val2 = pop_value(&val_stack);
            val1 = 0;
            res = calculate(val1, val2, exp[i]);
            push_value(&val_stack, to_string(res));
        }
        else if(exp[i] == '/')
        {
            val2 = pop_value(&val_stack);
            if(val2 == 0)
            {
                return "E";
            }
            else
            {
                val1 = pop_value(&val_stack);
                res = calculate(val1, val2, exp[i]);
                push_value(&val_stack, to_string(res));
            }
            
        }
        else
        {
            val2 = pop_value(&val_stack);
            val1 = pop_value(&val_stack);
            //cout << val1 <<" : " << val2 << endl;
            res = calculate(val1, val2, exp[i]);
            push_value(&val_stack, to_string(res));
        }
        
    }
    if(val_stack.top == 0)
    {
        return to_string(pop_value(&val_stack));
    }
    else
    {
        return "I";
    }  
}


/*  Function Name : check_balanced_prnts()
    Input :         expression
    Output:         0 or 1
    Description:    Returns 1 if the given expression is balanced else return 0. 
*/
int check_balanced_prnts(string expr)
{   
    optr_stack bracket_stack;
    bracket_stack.top = -1;

    push(&bracket_stack, '#');  

    for(int i=0; i<expr.length(); i++)
    {
        if(expr[i] == '(')
        {
            push(&bracket_stack, expr[i]);
        }
        if(expr[i] == ')')
        {
            if(stack_top(&bracket_stack) == '(')
                pop(&bracket_stack);
            else
            {
                return 0;
            }
        }
    }
    if(stack_top(&bracket_stack) == '#')
    {
        return 1;
    }
    else
    {
        return 0;
    }    
}


/*  Function Name : is_valid_operator()
    Input :         ch as a char type
    Output:         0 or 1
    Description:    Returns 1 if the given char is valid mathematical operator else return 0. 
*/
int is_valid_operator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '#')
        return 1;
    else
    {
        return 0;
    }   
}


/*  Function Name : is_valid()
    Input :         expression
    Output:         0 or 1
    Description:    Returns 1 if the given expression a valid else return 0. 
*/
int is_valid(string str)
{
    int index = -1;

    if(check_balanced_prnts(str) == 0)
        return 0;

    for(int i=0;i<str.length();i++)
    {
        if(str[i] == ' ' || str[i] == '\t' || str[i] == '.')
            continue;
        
        if(is_valid_operator(str[i]))
        {
            if(i==0 && str[i]!='#')
                return 0;
            
            if(i==str.length()-1)
                return 0;

            if(is_valid_operator(str[index]))
                return 0;
            
            if(str[index] == '(' && str[i] != '#')
                return 0;
        }

        else if (str[i] == '(')
        {
            if( i == str.length()-1 )
                return 0;
            
            if(i != 0 && (str[index] == ')' || str[index] == '.' || isdigit(str[index])))
            return 0;
        }
    
        else if(str[i] == ')')
        {
            if( i == 0)
                return 0;
            
            if(i!=0 && ((is_valid_operator(str[index]) || str[index] == '(')))
                return 0;
        }
        else if(isdigit(str[i]))
        {
            if(str[index] == ')')
                return 0;
        }
        else
        {
            return 0;
        }
        
        
        index = i;
    }
    return 1;
}


/*The driver function in which connection establish between server and client.
server performs fork operation for each client request and assign to each client to a process which will handle client request. 
*/
int main(int argc, char *argv[])
{
    int socket_fd, newsocket_fd;
    int port_num;
    socklen_t client_addr_size;
    int num_of_char;
    pid_t child_pid;

    ofstream input_file("server_records.txt");
    input_file.close();

    struct sockaddr_in server_addr, client_addr;

    if(argc < 2)
    {
        cout << "Error!!! Port number not provided\n";
        exit(1);
    }

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        perror("Error!!!, Socket call failed");
        exit(EXIT_FAILURE);
    }

    cout << "\nSocket call successful \n\n";

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

    if(listen(socket_fd, 5) < 0)
    {
        perror("Error!!!, Listening Failed");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        time_t begin, end;

        newsocket_fd  = accept(socket_fd, (struct sockaddr*)&client_addr, &client_addr_size);
        time(&begin);

        if(newsocket_fd < 0)
        {
            cout << "Unable to accept\n";
            exit(EXIT_FAILURE);
        }
            
        printf("Connected with client %s:%d \n\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        if((child_pid = fork()) == 0)
        {
            while (1)
            {
                char buffer[1024];
                bzero(buffer, 1024);
                num_of_char = read(newsocket_fd, buffer, 1023);
                if(num_of_char < 0)
                {
                    perror("Error!!! Reading Failed");
                    exit(EXIT_FAILURE);
                }

                if(buffer[0] == 'E')
                {
                    printf("Client %s:%d Exit\n\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                    break;
                }

                printf("Client ID %s:%d ",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                printf(" sent message  : %s\n", buffer);

                string output;
                string expression;
                string infix_2_postfix;
                string result;
                
                int inti = 0;
                char ch = '$';
                for(int i=0;i<strlen(buffer); i++)
                {
                    if(buffer[i] == '#')
                        expression = expression + '$';

                    if(!isdigit(ch) && ch != '.' && (buffer[i] == ' ' || buffer[i] == '\t'))
                        continue;
                    
                    if(ch == '(' && buffer[i] == '-')
                        expression = expression + '#';

                    else if(inti == 0 && buffer[i] == '-')
                        expression = expression + '#';

                    else 
                        expression = expression + buffer[i];

                    inti = 1;
                    ch = buffer[i];
                }

                if(is_valid(expression))
                {
                    infix_2_postfix = infix_to_postfix(expression);

                    if(infix_2_postfix == "I")
                    {
                        output = "Invalid Expression\n";
                    }
                    else
                    {
                        result = postfix_Eva(infix_2_postfix);
                        if(result == "I")
                            output = "Invalid Expression";
                        else if(result == "E")
                            output = "Error!!! Division by zero";
                        else
                        {
                            for(int i=0; i<infix_2_postfix.length(); i++)
                            {
                                if(infix_2_postfix[i] == '#')
                                    infix_2_postfix[i] = '-';
                            }
                            output = infix_2_postfix + ", " + result;

                            time(&end);
                            double time = 1.0 * (end - begin);          //calculating time
                            string IP = inet_ntoa(client_addr.sin_addr);
                            int p_nu = ntohs(client_addr.sin_port);
                            string file_ip = "Client ID: " + IP + ":" + to_string(p_nu) + " , " + "  Infix expression: " + buffer + " , "  +"  Postfix expression: " + infix_2_postfix + " , " + "  Answer: " + result + " , " + "  Time elapsed: " + to_string(time)+"sec";
                            ofstream out;                               // using file operation to write results on server_records.txt
                            out.open("server_records.txt", ios::app);
                            out << file_ip << "\n";
                            out.close();

                        }        
                    }
                }
                else
                {
                    output = "Invalid Expression\n";
                }
                
                cout << "Sending reply: "<<output <<endl<<endl;
                bzero(buffer, 1024);
                strcpy(buffer, output.c_str());

                num_of_char = write(newsocket_fd, buffer, strlen(buffer));
                if(num_of_char < 0)
                {
                    perror("Error while writing to socket");
                    exit(EXIT_FAILURE);
                } 
            }
            close(newsocket_fd);
            break;
        }
    }
    
    close(socket_fd);
    return 0;
}