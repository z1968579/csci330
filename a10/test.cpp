#include <iostream>
#include <string.h>
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

    DIR* pdir;
    int sockfd, newsockfd;
    char buffer[256];
    char* get[2];
    struct sockaddr_in server;
    struct sockaddr_in user;
    struct dirent* dir;
    struct stat stbuffer;
    socklen_t userlen = sizeof(user);

    cout << "Starting server" << endl;

    //Creating a new socket and checking to see if socket fails
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cerr << "Error: Failed to create socket\n";
        exit(2);
    }

    pdir = opendir(root);
    if (pdir == NULL)
    {
        cerr << "Error: Directory does not exist\n";
        exit(13);
    } 
    closedir(pdir);

    //Setting up the server
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));


    //Binds the socket to the server and checks to see if bind fails
    cout << "Binding socket" << endl;
    if ((bind(sockfd, (struct sockaddr*) &server, sizeof(server))) < 0)
    {
        cerr << "Error: Could not bind to port\n";
        exit(3);
    }

    //Listens for connections and checks to see if listen fails
    cout << "Listening to socket" << endl;
    if ((listen(sockfd, 64)) < 0)
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
        if ((newsockfd = accept(sockfd, (struct sockaddr*) &user, &userlen)) < 0)
        {
            cerr << "Error: Could not accept\n";
            exit(5);
        }


        //Splits connections for multiple users
        if (fork()) //Parent
        {
            cout << "New connection" << endl;
            close(newsockfd);
        }
        else //Child handles user requests
        {
            //Receives the request from the user and checks to see if the request failed
            if ((read(newsockfd, buffer, 256)) < 0)
            {
                cerr << "Error: Could not get request\n";
                exit(6);
            }

            cout << "User request: " << buffer << endl;

            //Checks for GET request
            get[0] = strtok(buffer, " ");
            if (strcmp(get[0], "GET") == 0)
            {
                get[1] = strtok(NULL, " \n");

                //Checks for '/'
                if (get[1][0] != '/')
                {
                    char error[] = "Error: GET request must start with /\n";
                    write(newsockfd, error, strlen(error));
                    exit(7);
                }

                //Checks for '..'
                if (strstr(get[1], "..") != NULL)
                {
                    char error[] = "Error: GET request cannot contain \"..\"\n";
                    write(newsockfd, error, strlen(error));
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
                    stat(root, &stbuffer);
                    if ((stbuffer.st_mode &S_IFMT) == S_IFREG)
                    {
                        printFile(root, newsockfd);
                        close(newsockfd);
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
                    if ((stat(path, &stbuffer)) == 0)
                    {
                        printFile(path, newsockfd);
                        close(newsockfd);
                        exit(9);
                    }
                }

                //Opens directory and checks for error
                //pdir = opendir(root);
                if ((pdir = opendir(root)) == NULL)
                {
                    char error[] = "Error: File or directory does not exist\n";
                    write(newsockfd, error, strlen(error));
                    exit(10);
                } 

                //dup2 newsockfd to stdout
                if (dup2(newsockfd, 1) < 0)
                {
                    cerr << "Error: dup2 failed\n";
                    exit(11);
                }

                //Prints directory contents
                while ((dir = readdir(pdir)) != NULL)
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
                write(newsockfd, error, strlen(error));
            }

            close(newsockfd);
            exit(12);
        }

        //buffer to null
        memset(buffer, 0, sizeof(buffer));
    }

    close(sockfd);
    return 0;
}

//printFile Function
//Sends contents of requested file to a set
//file descriptor
/**
 * @brief Prints the contents of a file to a file descriptor like cat
 * 
 * @param path_name The path of the file to be printed
 * @param fd 
 */
void printFile(char* path_name, int fd)
{
    int open_fd;
    char buffer[1024];
    ssize_t nr;
    
    open_fd = open(path_name, O_RDONLY);

    if (open_fd < 0)
    {
        char error[] = "Error: File does not exist\n";
        write(fd, error, strlen(error));
        exit(1);
    }

    nr = read(open_fd, buffer, 1024);
    write(fd, buffer, nr);

    while (nr >= 1024)
    {
        nr = read(open_fd, buffer, 1024);
        write(fd, buffer, nr);
    }
}

