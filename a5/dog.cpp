 /**
 * @file dog.cpp
 * @author Jacob Rudawski z1968579
 * @brief CSCI 330 Assignment 5
 * @date 10/03/2022
 */

#include "dog.h"

void caesar(char* buffer, ssize_t nr, ssize_t shift_size)
{

}
void byte(char* buffer, ssize_t nr, ssize_t shift_size)
{

}
char* hex(char* buffer, ssize_t nr)
{
    return buffer;
}
char* binary(char* buffer, ssize_t nr)
{   
    char *binary = (char*) malloc(nr*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(ssize_t i = 0; i < nr; ++i) {
        char ch = buffer[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

ssize_t min (ssize_t a, ssize_t b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
