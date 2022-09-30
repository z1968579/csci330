//***************************************************************************
//
//  a4-z1968579.cpp
//  CSCI 330 Assignment 4  9/26/2022
//  
//  Created by Jacob Rudawski z1968579
//
//***************************************************************************
#include <iostream>

#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
    int fd, truncate = 0;
    char *file, *input; //pointers
    struct stat st;
    cout << argv[1] << endl;

    if(argc < 3) //prints usage of program if no parameters are in and creates a default file called log if it does not exist.
    {
        cout << ("Usage : seclog [-c] out_file message_string");
        cout << ("\nwhere the message_string is appended to the out_file.");
        cout << ("\nThe -c option clears the file before the message is appended\n");


        int fg = open("log" , O_WRONLY | O_CREAT | 0x0); //Creates log
        cout << "\nCreated default file: 'log'\n" << endl;
        chmod("log", 0x0); // changes log privileges

        return -1;
    }

    int opt; char optstring[] = {'c'}; //declares opt and created cstring for -c detection
    while((opt = getopt(argc, argv, optstring)) != -1)  //looks for -c in any order 
    { 
        switch(opt) 
        { 
        case 'c':
            truncate = O_TRUNC; //enables truncation
            break;
        default:
            break;
        }
    }

    file = argv[optind]; //points file to first argument after -c
    input = argv[optind + 1]; //points input to second argument after -c
    
    if(stat(file, &st) != 0) //Gets permissions for the file
    {
        perror(file);
        return -1;
    }


    if (st.st_mode & 0x1ff) //if file has any privileges it errors and ignores
    {
        cout << file <<" is not secure, ignoring\n";
        return 1;
    }

    if(chmod(file, 0x180)) //gives privileges
        perror("failed");

    fd = open(file, O_WRONLY | O_APPEND | truncate); //opens file and if -c case was enabled it clears file

    //check if open system call failed.
    if (fd == -1)
    {
        perror("failed system call");
        return -1;
    }

    write(fd, input, strlen(input)); //input
    write(fd, "\n", 1);

    close(fd); //closes fd

    chmod(file, 0x0); //changes privileges to none

    return 0;
}