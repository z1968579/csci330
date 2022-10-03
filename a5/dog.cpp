 /**
 * @file dog.cpp
 * @author Jacob Rudawski z1968579
 * @brief CSCI 330 Assignment 5
 * @date 10/03/2022
 */

#include "dog.h"

void caesar(char* buffer, ssize_t len, ssize_t shift_size)
{
    char t;
    for (int i = 0; i <= len - 1; i++)
    {
        t = buffer[i];
        if(isupper(t))
        {
            t = ((t - 'A' + ((shift_size % 26) + 26)) % 26) + 'A';
        }
        else if (islower(t))
        {
            t = ((t - 'a' + ((shift_size % 26) + 26)) % 26) + 'a';
        }
        buffer[i] = t;
    }
}
void byte(char* buffer, ssize_t len, ssize_t shift_size)
{
    for (int i = 0; i <= len - 1; i++)
    {
        buffer[i] = (((int) buffer[i] + shift_size) % 256);
    }
}
void hex(char* buffer, ssize_t len, char* out)
{
    char hexadecimal[] = "0123456789adcdef";
    for(int i = 0; i <= len - 1; i++)
    {
        out[i * 2 + 0] = hexadecimal[(buffer[i] & 0xF0) >> 4];
        out[i * 2 + 1] = hexadecimal[(buffer[i] & 0x0F) >> 0];
    }
}
void binary(char* buffer, ssize_t len, char* out)
{   
    for(int i = 0; i <= len - 1; i++)
    {
        for (int j = 0; j < 8; j++)
        {
        out[i * 8 + j] = ((buffer[i] & (1 << (7 - j))) >> (7 - j)) + 48;
        }
    }
}
void digit(char* optarg)
{
    int i = 0;
    char arg = optarg[i];
    if (isdigit(arg) == false)
    {
        std::cerr << "Error: not a valid argument for option" << std::endl;
        exit(0);
    }
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
