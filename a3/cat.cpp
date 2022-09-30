//***************************************************************************
//
//  cat.cpp
//  CSCI 330 Assignment 3   9/16/2022
//  
//  Created by Jacob Rudawski z1968579
//
//***************************************************************************
#include <iostream>
#include <iomanip>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <cstring>


void input(int fd, char buffer[]);

using namespace std;

int main(int argc, char *argv[])
{
    int fd;
    ssize_t nr;

    if(argc > 1) //checks for no file input
    {
        for(int i = 1; i < argc; i++) //loops for multiple files
        {
            char buffer[10000];

            if (strcmp(argv[i],"-") == 0)//checks for - 
            {
                fd = STDIN_FILENO;
            }
            else 
            {
                fd = open(argv[i], O_RDONLY, 0644);
            }
            input(fd, buffer);
        } 
    }
    else
    {
        cout << "No files listed as argument" << endl; 
        exit(1);
    }
    return 0;
}

/* when "-" case is true, takes user input.
@param fd is the file discriptor 
@param buffer[] array that stores characters */
void input(int fd, char buffer[])
{
    ssize_t nw;
    int nr;
    while ((nr = read(fd, buffer, 10000)) > 0)
    {
      nw = write(1, buffer, nr);
    }
    close(fd);
    return;
}
