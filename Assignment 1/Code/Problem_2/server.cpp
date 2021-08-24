/*  Name : Pratibha Singh (pratibhasingh@kgpian.iitkgp.ac.in)
    Roll No : 20CS60R12

    File name : server.cpp
    Date : Jan 8 , 2021
    Description :The task is to Creates a socket and listens on some specific port to process client
                request. There is a default file present having n lines and the server should be able
                to process EVALUATEX and WRITEX request from the client.

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

#define MAX 1000                 // For stack Max Size
using namespace std;

struct value                    // For value stack
{
    int top;
    string data[MAX];
};

struct optr                     // For operator stack
{
    int top;
    char op[MAX];
};


/*  Function Name : push_value()
    Input :         value_stack reference, string
    Output:         push string
    Description:    push element to value_stack. 
*/
void push_value(struct value *stack, string str)
{
    if(stack->top == MAX-1)
    {
        cout << "Stack Overflow\n";
        exit(1);
    }
    else
    {
        stack->top++;
        stack->data[stack->top] = str;
    }   
}


/*  Function Name : push_optr()
    Input :         optr_stack reference, op
    Output:         push op
    Description:    push operator to optr_stack. 
*/
void push_optr(struct optr *stack, char op)
{
    if(stack->top == MAX-1)
    {
        cout << "Stack Overflow\n";
        exit(1);
    }
    else
    {
        stack->top++;
        stack->op[stack->top] = op;
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


/*  Function Name : pop_optr()
    Input :         optr_stack reference
    Output:         pop element
    Description:    pop element from optr_stack. 
*/
void pop_optr(struct optr *stack)
{
    stack->op[(stack->top)--];
}


/*  Function Name : optr_top()
    Input :         optr_stack reference
    Output:         char
    Description:    Returns optr_stack top element. 
*/
char optr_top(struct optr *stack)
{
    return (stack->op[(stack->top)]);
}


/*  Function Name : check_balanced_prnts()
    Input :         expression
    Output:         0 or 1
    Description:    Returns 1 if the given expression is balanced else return 0. 
*/
int check_balanced_prnts(string expr)
{   
    optr bracket_stack;
    bracket_stack.top = -1;

    push_optr(&bracket_stack, '#');  

    for(int i=0; i<expr.length(); i++)
    {
        if(expr[i] == '(')
        {
            push_optr(&bracket_stack, expr[i]);
        }
        if(expr[i] == ')')
        {
            if(optr_top(&bracket_stack) == '(')
                pop_optr(&bracket_stack);
            else
            {
                return 0;
            }
        }
       
        if(optr_top(&bracket_stack) == '#')
        {
            return 1;
        }
        else
        {
            return 0;
        }    
    }
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
        case '^':   return pow(a,b);
        case '*':   return a*b;
        case '/':   return a/b;
        case '%':   return fmod(a,b);
        case '+':   return a+b;
        case '-':   return a-b;    
    }
}


/*  Function Name : check_precedence()
    Input :         optr
    Output:         0 or 1 or 2 or 3
    Description:    This function computes precendence order of operators and return appropriate value. 
*/
int check_precedence(char op)
{
    if(op == '+' || op == '-')
        return 1;
    if(op == '*' || op == '/' || op == '%')
        return 2;
    if(op == '^')
        return 3;
    
    return 0;
}


/*  Function Name : EvaluateX()
    Input :         expression
    Output:         result as string type
    Description:    Compute infix expression and returns its result if valid string and returns appropriate message if invalid string. 
*/
string EvaluateX(string str)
{
    string output;
    double val1, val2;
    char op;

    value val_stack;
    optr optr_stack;

    val_stack.top = -1;
    optr_stack.top = -1;

    push_optr(&optr_stack, '#');

    if(isdigit(str[str.length()-1]) || (str[str.length()-1] == ')') || (str[str.length()-1] == ' ') || (str[str.length()-1] == '\t'))    //checking if last char of given expr valid or not
    {
        for(int i=0; i<str.length(); i++)
        {
            if(isdigit(str[i]) || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '%' || str[i] == '(' || str[i] ==')' || str[i] == '.' || str[i] == ' ' || str[i] == '\t')
            {
                if(str[i] == ' ')
                continue;
            
                else if(str[i] == '(')
                {
                    push_optr(&optr_stack, str[i]);
                }
                else if(isdigit(str[i]) || str[i] == '.')
                {
                    string num;
                    int count = 0;
                    if(str[i] == '.')
                    {
                        count++;
                        num = num + str[i];
                        i++;
                    }

                    while(i<str.length() && (isdigit(str[i]) || str[i] == '.'))
                    {
                        if(str[i] == '.')
                            count++;
                        
                        if(count < 2)
                        {
                            num = num + str[i];
                            i++;
                        }
                        else
                        {
                            output = "Invalid Expression\n";
                            return output;
                        }    
                    }
                    push_value(&val_stack, num);
                    i--;
                }
                else if(str[i] == ')')
                {
                    while(optr_top(&optr_stack) != '#' && optr_top(&optr_stack) != '(')
                    {
                        val2 = pop_value(&val_stack);
                        if((optr_top(&optr_stack) == '+' || optr_top(&optr_stack) == '-') && (val_stack.top == -1))
                        {
                            val1 = pop_value(&val_stack);
                            op = optr_top(&optr_stack);
                            pop_optr(&optr_stack);

                            string s = to_string(calculate(val1, val2, op));
                            push_value(&val_stack, s);
                        }
                        else if(val_stack.top != -1)
                        {
                            val1 = pop_value(&val_stack);
                            op = optr_top(&optr_stack);
                            pop_optr(&optr_stack);

                            string s = to_string(calculate(val1, val2, op));
                            push_value(&val_stack, s);
                        }
                        else
                        {
                            output = "Invalid Expression\n";
                            return output; 
                        }
                    }
                    if(optr_top(&optr_stack) != '#')
                        pop_optr(&optr_stack);
                }
                else
                {
                    while((optr_top(&optr_stack) != '#') && check_precedence(optr_top(&optr_stack)) >= check_precedence(str[i]) && !(optr_top(&optr_stack) == '^' && str[i] == '^'))
                    {
                        val2 = pop_value(&val_stack);
                        if((optr_top(&optr_stack) == '+' || optr_top(&optr_stack) == '-') && (val_stack.top == -1))
                        {
                            val1 = pop_value(&val_stack);
                            op = optr_top(&optr_stack);
                            pop_optr(&optr_stack);

                            string s = to_string(calculate(val1, val2, op));
                            push_value(&val_stack, s);
                        }
                        else if(val_stack.top != -1)
                        {
                            val1 = pop_value(&val_stack);
                            op = optr_top(&optr_stack);
                            pop_optr(&optr_stack);

                            string s = to_string(calculate(val1, val2, op));
                            push_value(&val_stack, s);
                        }
                        else
                        {
                            output = "Invalid Expression\n";
                            return output; 
                        }
                    }
                    push_optr(&optr_stack, str[i]);
                }
            }
            else
            {
                output = "Invalid Expression\n";
                return output;
            }
        } 

        if(val_stack.top == -1)
        {
            output = "Expression doesn't exist\n";
            return output;        
        }

        while(optr_top(&optr_stack) != '#')
        {
            val2 = pop_value(&val_stack);
            if((optr_top(&optr_stack) == '+' || optr_top(&optr_stack) == '-') && (val_stack.top == -1))
            {
                val1 = pop_value(&val_stack);
                op = optr_top(&optr_stack);
                pop_optr(&optr_stack);

                string s = to_string(calculate(val1, val2, op));
                push_value(&val_stack, s);
            }
            else if(val_stack.top != -1)
            {
                val1 = pop_value(&val_stack);
                op = optr_top(&optr_stack);
                pop_optr(&optr_stack);

                string s = to_string(calculate(val1, val2, op));
                push_value(&val_stack, s);
            }
            else
            {
                output = "Invalid Expression\n";
                return output; 
            } 
        }
        
        if(optr_top(&optr_stack) == '#')
        {
            double res =  pop_value(&val_stack);
            return(to_string(res));
        }
        else
        {
            output = "Invalid Expression\n";
            return output;
        }
    }
    else
    {
        output = "Invalid Expression";
        return output;
    }    
}


/*  Function Name : simplify()
    Input :         expression
    Output:         string type result
    Description:    This function returns value after removal of outermost bracket if it is valid after bracket
                    removal else return value as it is.
*/
string simplify(string expr)
{
    int i = 0;
    int j = expr.length() -1;
    string str;

    while(expr[i] == '(' && expr[j] == ')')
    {
        i++;
        j--;
    } 
    for(int k = i; k<=j; k++)
    {
        str = str + expr[k];
    }
    int flag = check_balanced_prnts(str);
    if(flag == 1)
        return str;
    else
    {
        return expr;
    }   
}


/*  Function Name : WriteX()
    Input :         expression
    Output:         1 or 2 or 3
    Description:    This function resturns:
                    1. if given expression is invalid
                    2. if given expression already exists in the input.txt file
                    3. if given expression is valid and doesn't exist in input.txt file.
*/
int WriteX(string expr)
{
    string result = EvaluateX(expr);
    string output;
    if(result[0] == 'I')
    {
        return 1;
    }
    else
    {
        string querry1 = simplify(expr);
        ifstream input_file("input.txt");       //reading from input.txt file
        string line;

        cout <<"querry :"<<querry1 <<endl;
        while(getline(input_file, line))
        {
            string str;

            for(int i=0;i<line.length();i++)
            {
                if(line[i] == ' ')
                    continue;
                else
                {
                    str = str + line[i];
                }
            }

            string querry2 = simplify(str);
            //cout <<"ori expr: "<<expr <<"querry: " << querry1<<endl<< "querry 2:" <<querry2<<endl;

            if(querry1 == querry2)
            {
                return 2;
            }
        }
        input_file.close();
    }    
    return 3;
}

/*The driver function in which connection establish between server and client.
server performs appropriate operations after getting command(EvaluateX and WriteX) from the client. 
*/
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

        if(buffer[0] == 'E')            //If command passed by client is EvaluateX
        {
            string str, output;
            int flag = 0;
            for(int i=1; i<strlen(buffer); i++)
            {
                if(buffer[i] == '\0')
                    break;
                
                if((buffer[i]>='0' && buffer[i]<='9') || buffer[i] == ' ')
                {
                    str = str+buffer[i];
                }
                else
                {
                    flag = 1;
                    break;
                }    
            }
            if(flag == 1)
            {
                output = "Invalid Input\n";
            }
            else
            {
                int line_num = stoi(str);
                ifstream input_file("input.txt");       //opeining input.txt file
                int count = 1;

                string line,str;

                while(getline(input_file, line))
                {
                    if(count == line_num)
                    {
                        str = line;
                        break;
                    }
                    count++;
                }

                if(str.length() == 0)
                {
                    output = "Expression doesn't exit\n";
                }
                else
                {
                    output = EvaluateX(str);
                }
                input_file.close();    
            }
            
            string c_msg;
            c_msg = "EVALUATEX " + str;
            cout << "Client Message : "<<c_msg<<endl;
            cout <<"\n";
            bzero(buffer, 256);
            strcpy(buffer, output.c_str());
            num_of_char = write(newsocket_fd, buffer, strlen(buffer));
            if(num_of_char < 0)
            {
                perror("Error!!! Writing Failed");
                exit(EXIT_FAILURE);
            }

        }

        else if(buffer[0] == 'W')           //If command passed by client is Writex
        {
            string expr;

            for(int i=1; i<strlen(buffer);i++)
            {
                if(expr[i] == ' ')
                    continue;
                else
                {
                    expr = expr + buffer[i];
                }    
            }

            string output;
            int flag;
            flag = WriteX(expr);
            
            string c_msg;
            
            string expression;
            for(int i=1; i<strlen(buffer); i++)
            {
                expression = expression + buffer[i];
            }
            c_msg = "WRITEX "+ expression;
            cout << "Client Message : "<<c_msg<<endl;
            cout << "\n";

            if(flag == 1)
            {
                output = "Invalid Expression!!! Enter a Valid Expression";
                bzero(buffer, 256);
                strcpy(buffer, output.c_str());
                num_of_char = write(newsocket_fd, buffer, strlen(buffer));
                if(num_of_char < 0)
                {
                    perror("Error!!! Writing Failed");
                    exit(EXIT_FAILURE);
                }
            }
            else if(flag == 2)
            {
                output = "Expression Already Exist";
                bzero(buffer, 256);
                strcpy(buffer, output.c_str());
                num_of_char = write(newsocket_fd, buffer, strlen(buffer));
                if(num_of_char < 0)
                {
                    perror("Error!!! Writing Failed");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {   
                string expression;
                for(int i=1; i<strlen(buffer); i++)
                {
                    expression = expression + buffer[i];
                }

                ofstream out;               //opening file to append
                out.open("input.txt", ios::app);
                out << expression <<"\n";

                output = "Expression added successfully";
                bzero(buffer, 256);
                strcpy(buffer, output.c_str());
                num_of_char = write(newsocket_fd, buffer, strlen(buffer));
                if(num_of_char < 0)
                {
                    perror("Error!!! Writing Failed");
                    exit(EXIT_FAILURE);
                }

                out.close();
            }    
        }
        else
        {
            string output = "Invalid Command\n";
            bzero(buffer, 256);
            strcpy(buffer, output.c_str());
            num_of_char = write(newsocket_fd, buffer, strlen(buffer));
            if(num_of_char < 0)
            {
                perror("Error!!! Writing Failed");
                exit(EXIT_FAILURE);
            }
        }
        cout << "\n\n*************************************************************************\n\n";
    }
    close(newsocket_fd);
    close(socket_fd);

    return 0;
}