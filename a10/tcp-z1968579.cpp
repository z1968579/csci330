 /**
 * @file tcp-z1968579.cpp
 * @author Jacob Rudawski z1968579
 * @brief CSCI 330 Assignment 10
 * @date 11/30/2022
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

using namespace std;

void printFile(char*, int);

int main(int argc, char *argv[])
{
    char* port = argv[1];
    char* root = argv[2];

    if (argc != 3) //Checks arguments
    {
        cerr << "Error: Not enough arguments\nUsage: " << argv[0] << " (port) (directory)" << endl;
        exit(1);
    }

    DIR* p_dir;
    int sock_fd, new_sock_fd;
    char buffer[256];
    char* get[2];
    struct sockaddr_in server;
    struct sockaddr_in user;
    struct dirent* dir;
    struct stat st_buffer;
    socklen_t user_len = sizeof(user);

    cout << "Starting server" << endl;

    //Creating a new socket and checking to see if socket fails
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cerr << "Error: Failed to create socket\n";
        exit(2);
    }

    if ((p_dir = opendir(root)) == NULL)
    {
        cerr << "Error: Directory does not exist\n";
        exit(13);
    } 
    closedir(p_dir);

    //Setting up the server
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));


    //Binds the socket to the server and checks to see if bind fails
    cout << "Binding socket" << endl;
    if ((bind(sock_fd, (struct sockaddr*) &server, sizeof(server))) < 0)
    {
        cerr << "Error: Could not bind to port\n";
        exit(3);
    }

    //Listens for connections and checks to see if listen fails
    cout << "Listening to socket" << endl;
    if ((listen(sock_fd, 64)) < 0)
    {
        cerr << "Error: Could not listen\n";
        exit(4);
    }

    cout << "Server is running on port: " << port << endl;
    cout << "Waiting for connection" << endl;
   
    //loops until the server is killed/breaks
    while (true)
    {
        //Accepts users and checks to see if the connection failed
        if ((new_sock_fd = accept(sock_fd, (struct sockaddr*) &user, &user_len)) < 0)
        {
            cerr << "Error: Could not accept\n";
            exit(5);
        }

        //Splits connections for multiple users
        if (fork()) //Parent
        {
            char* ip = inet_ntoa(user.sin_addr);
            cout << "New connection from: " << ip <<  endl;
            close(new_sock_fd);
        }
        else //Child handles user requests
        {
            //Receives the request from the user and checks to see if the request failed
            if ((read(new_sock_fd, buffer, 256)) < 0)
            {
                cerr << "Error: Could not get request\n";
                exit(6);
            }

            cout << "User request: " << buffer;

            //Checks for GET request
            get[0] = strtok(buffer, " ");
            if (strcmp(get[0], "GET") == 0)
            {
                get[1] = strtok(NULL, " \n");

                //Checks for '/'
                if (get[1][0] != '/')
                {
                    char error[] = "Error: GET request must start with /\n";
                    write(new_sock_fd, error, strlen(error));
                    exit(7);
                }

                //Checks for '..'
                if (strstr(get[1], "..") != NULL)
                {
                    char error[] = "Error: GET request cannot contain \"..\"\n";
                    write(new_sock_fd, error, strlen(error));
                    exit (7);
                }

                for (char *p = get[1] + strlen(get[1])-1; *p == '\r' || *p == '\n'; p--)//replaces new lines and returns with null
                {
                    *p = '\0';
                }

                strcat(root, get[1]);

                //Checks for '/'
                if (root[strlen(root) - 1] != '/')
                {
                    //Checks for file path
                    stat(root, &st_buffer);
                    if ((st_buffer.st_mode &S_IFMT) == S_IFREG)
                    {
                        printFile(root, new_sock_fd);
                        close(new_sock_fd);
                        exit(8);
                    }
                }
                else //Path refers to a directory
                {    
                    char path[128];
                    strcpy(path, root);
                    strcat(path, "index.html");

                    for (char *p = path + strlen(path)-1; *p == '\r' || *p == '\n'; p--)
                    {
                        *p = '\0';
                    }
                    
                    //Checks for index.html
                    if ((stat(path, &st_buffer)) == 0)
                    {
                        printFile(path, new_sock_fd);
                        close(new_sock_fd);
                        exit(9);
                    }
                }

                //Opens directory and checks for error
                //p_dir = opendir(root);
                if ((p_dir = opendir(root)) == NULL)
                {
                    char error[] = "Error: File or directory does not exist\n";
                    write(new_sock_fd, error, strlen(error));
                    exit(10);
                } 

                //dup2 new_sock_fd to stdout
                if (dup2(new_sock_fd, 1) < 0)
                {
                    cerr << "Error: dup2 failed\n";
                    exit(11);
                }

                //Prints directory contents
                while ((dir = readdir(p_dir)) != NULL)
                {
                    if (dir->d_name[0] != '.')
                    {
                        cout << dir->d_name << endl;
                    }
                }

            }
            else //Error if request is not GET
            {
                char error[] = "Request must start with GET\n";
                write(new_sock_fd, error, strlen(error));
            }

            close(new_sock_fd);
            exit(12);
        }

        //buffer to null
        memset(buffer, 0, sizeof(buffer));
    }

    close(sock_fd);
    return 0;
}


/**
 * @brief Prints the contents of a file to a file descriptor like cat
 * 
 * @param path_name The path of the file to be printed
 * @param fd sock_fd
 */
void printFile(char* path_name, int fd)
{
    int open_fd;
    char buffer[1024];
    ssize_t nr;
    
    open_fd = open(path_name, O_RDONLY);

    while ((nr = read(open_fd, buffer, 1024)) > 0)
    {
        write(fd, buffer, nr);
    }
}

