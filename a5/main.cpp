/**
 * @file main.cpp
 * @author Jacob Rudawski z1968579
 * @brief CSCI 330 Assignment 5
 * @date 10/03/2022
 */
#include <iostream>
#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <string.h>
#include "dog.h"
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int fd, opt;

    char *buffer = nullptr;

    ssize_t nr;
    ssize_t buffer_size = SIZE_BUFFER;
    ssize_t user_bytes = 0;
    ssize_t total_read = 0;
    ssize_t shift_size = 0;

    bool nflag = false, 
    Cflag = false, 
    rflag = false, 
    Xflag = false, 
    Bflag = false;

    if(argc == 1) //checks for no file input
    {
        perror("No files listed as argument"); 
        return 1;
    }
    for(int i = 1; i < argc; i++) //loops for multiple files
    {
        char optstring[] = "b:n:C:r:XB";
        while((opt = getopt(argc, argv, optstring)) != -1)  //looks for -c in any order 
        { 
            switch(opt) 
            { 
            case 'b':
                buffer_size = atoi(optarg);
                break;
            case 'n':
                user_bytes = atoi(optarg);
                nflag = true;
                break;
            case 'C':
                Cflag = true;
                shift_size = atoi(optarg);

                if (Cflag == true && rflag == true)
                {
                    cerr << "Warning: -C and -r were given exiting" << endl;
                    return 3;
                }
                break;
            case 'r':
                rflag = true;
                shift_size = atoi(optarg);
                if (Cflag == true && rflag == true)
                {
                    cerr << "Warning: -C and -r were given exiting" << endl;
                    return 4;
                }
                break;
            case 'X':
                Xflag = true;

                if (Xflag == true && Bflag == true)
                {
                    cerr << "Warning: -X and -B were given exiting" << endl;
                    return 5;
                }
                break;

            case 'B':
                Bflag = true;

                if (Xflag == true && Bflag == true)
                {
                    cerr << "Warning: -X and -B were given exiting" << endl;
                    return 6;
                }
                break;
            default:
                return 2;
                break;
            }
        }
    } 

    buffer = new char[buffer_size];

    for (int i = optind; i < argc; i++)
    {
        if (strcmp(argv[optind],"-") == 0)
        {
            fd = STDIN_FILENO;
        }
        else 
        {
            fd = open(argv[i], O_RDONLY, 0644);
        }

        //Reads file
        while ((nr = read(fd, buffer, nflag ? min(buffer_size, (user_bytes - total_read)) : buffer_size)) > 0)
        {
            
            total_read += nr;
            
            if (Cflag == true )
            {
                caesar(buffer, nr, shift_size);
            }
            if (rflag == true)
            {
                byte(buffer, nr, shift_size);
            }
            if (Xflag == true)
            {
                hex(buffer, nr);
            }
            if (Bflag == true)
            {
                binary(buffer, nr);
            }
            write(1, buffer, nr);
            
        }
        //Closes file 
        if (fd == STDIN_FILENO)
        {
            close(fd);
        }
    }
    delete[] buffer;  
    return 0;
}
