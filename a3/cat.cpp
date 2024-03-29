//***************************************************************************
//
//  cat.cpp
//  CSCI 330 Assignment 3   9/16/2022
//  
//  Created by Jacob Rudawski z1968579
//
//***************************************************************************
#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <string.h>
#define BUFFER_SIZE 4096
int main(int argc, char *argv[])
{
    int fd;
    ssize_t nr;
    if(argc == 1) //checks for no file input
    {
        perror("No files listed as argument"); 
        return 1;
    }

    for(int i = 1; i < argc; i++) //loops for multiple files
    {
        char buffer[BUFFER_SIZE];
        //Checks if file name is a dash 
        if (strcmp(argv[i],"-") == 0)
        {
            fd = STDIN_FILENO;
        }
        else 
        {
            fd = open(argv[i], O_RDONLY, 0644);
        }
        //Reads file
        while ((nr = read(fd, buffer, BUFFER_SIZE)) > 0)
        {
            write(1, buffer, nr);
        }
        //Closes file 
        if (fd == STDIN_FILENO)
        {
            close(fd);
        }
        
    } 
    return 0;
}
