/**
 * @file main.cpp
 * @author Jacob Rudawski z1968579
 * @brief CSCI 330 Assignment 5
 * @date 10/03/2022
 */
#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <string.h>
#include "dog.h"
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
        int opt; 
        char optstring[] = "b:n:C:r:XB"; //declares opt and created cstring for -c detection
        while((opt = getopt(argc, argv, optstring)) != -1)  //looks for -c in any order 
        { 
            switch(opt) 
            { 
            case 'b':

                break;
            case 'n':

                break;
            case 'C':
               // d.caesar();
                break;
            case 'r':

                break;
            case 'X':

                break;

            case 'B':

                break;
            default:

                break;
            }
        }
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
