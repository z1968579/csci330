/**
 * @file main.cpp
 * @author Jacob Rudawski z1968579
 * @brief CSCI 330 Assignment 5
 * @date 10/03/2022
 */

#include "dog.h"

using std::cerr;
using std::endl;

int main(int argc, char* argv[])
{
    int fd, opt;
    //buffers for options
    char *buffer = nullptr;
    char *hex_buffer = nullptr;
    char *binary_buffer = nullptr;

    ssize_t nr;
    ssize_t buffer_size = SIZE_BUFFER;
    ssize_t user = 0;
    ssize_t total = 0;
    ssize_t shift = 0;

    bool nflag = false, 
    Cflag = false, 
    rflag = false, 
    Xflag = false, 
    Bflag = false;

    if(argc == 1) //checks for no file input
    {
        cerr << "No files listed as argument" << endl;
        return 1;
    }
    for(int i = 1; i < argc; i++) //loops for multiple files
    {
        char optstring[] = "b:n:C:r:XB";
        while((opt = getopt(argc, argv, optstring)) != -1) 
        { 
            switch(opt) 
            { 
            case 'b':
                digit(optarg); //sends optarg to be error checked
                buffer_size = atoi(optarg); //converts optarg into ssize_t and stores it in buffer
                break;
            case 'n':
                digit(optarg);
                user = atoi(optarg);
                nflag = true;
                break;
            case 'C':
                digit(optarg);
                shift = atoi(optarg); 
                Cflag = true;
                if (Cflag == true && rflag == true) 
                {
                    cerr << "Warning: -C and -r were given. Exiting" << endl;
                    return 3;
                }
                break;
            case 'r':
                digit(optarg);
                rflag = true;
                shift = atoi(optarg);
                if (Cflag == true && rflag == true)
                {
                    cerr << "Warning: -C and -r were given. Exiting" << endl;
                    return 4;
                }
                break;
            case 'X':
                Xflag = true;
                if (Xflag == true && Bflag == true)
                {
                    cerr << "Warning: -X and -B were given. Exiting" << endl;
                    return 5;
                }
                break;

            case 'B':
                Bflag = true;
                if (Xflag == true && Bflag == true)
                {
                    cerr << "Warning: -X and -B were given. Exiting" << endl;
                    return 6;
                }
                break;
            default:
                return 2;
                break;
            }

        }
    } 
    //creates new buffers for conditions
    buffer = new char[buffer_size];
    hex_buffer = new char[buffer_size * 2];
    binary_buffer = new char[buffer_size * 8 + 1];

    for (int i = optind; i < argc; i++)
    {
        if (strcmp(argv[optind],"-") == 0) //checks for - case
        {
            fd = STDIN_FILENO;
        }
        else 
        {
            fd = open(argv[i], O_RDONLY, 0644);
        }
        //Reads file and checks for nflag condition
        while ((nr = read(fd, buffer, nflag ? min(buffer_size, (user - total)) : buffer_size)) > 0)
        {
            
            total += nr;
            if (Cflag == true )
            {
                caesar(buffer, nr, shift);
            }
            if (rflag == true)
            {
                byte(buffer, nr, shift);
            }
            if (Xflag == true)
            {
                hex(buffer, nr, hex_buffer);
                write(1, hex_buffer, nr * 4);
            }
            else if (Bflag == true)
            {
                binary(buffer, nr, binary_buffer);
                write(1, binary_buffer, nr * 8);
            }
            else
            {
            write(1, buffer, nr);
            }
            
        }
        //Closes file 
        if (fd == STDIN_FILENO)
        {
            close(fd);
        }
    }
    delete[] buffer;  
    delete[] hex_buffer;
    delete[] binary_buffer;
    return 0;
}
