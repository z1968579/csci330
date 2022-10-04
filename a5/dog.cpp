 /**
 * @file dog.cpp
 * @author Jacob Rudawski z1968579
 * @brief CSCI 330 Assignment 5
 * @date 10/03/2022
 */

#include "dog.h"

/**
 * @brief caesar shift function
 * 
 * @param buffer pointer to buffer
 * @param len length of buffer or nr
 * @param shift how much to shift by
 */
void caesar(char* buffer, ssize_t len, ssize_t shift)
{
    char t; //temp
    for (int i = 0; i <= len - 1; i++) //loop through buffer
    {
        t = buffer[i];
        //checks for either lowercase or uppercase then caesar shift
        if(isupper(t))
        {
            t = ((t - 'A' + ((shift % 26) + 26)) % 26) + 'A';
        }
        else if (islower(t))
        {
            t = ((t - 'a' + ((shift % 26) + 26)) % 26) + 'a';
        }
        buffer[i] = t;
    }
}
/**
 * @brief byte rotation function
 * 
 * @param buffer pointer to buffer
 * @param len length of buffer or nr
 * @param shift how much to shift by
 */
void byte(char* buffer, ssize_t len, ssize_t shift)
{
    for (int i = 0; i <= len - 1; i++)
    {
        buffer[i] = (((int) buffer[i] + shift) % 256); //byte rotation
    }
}
/**
 * @brief changes hex_buffer for output
 * 
 * @param buffer pointer to buffer
 * @param len length of buffer or nr
 * @param out the hex_buffer that will be changed and outputed later
 */
void hex(char* buffer, ssize_t len, char* out)
{
    char hexadecimal[] = "0123456789adcdef"; 
    for(int i = 0; i <= len - 1; i++)
    {
        out[i * 2 + 0] = hexadecimal[(buffer[i] & 0xF0) >> 4]; //changes first spot to hex
        out[i * 2 + 1] = hexadecimal[(buffer[i] & 0x0F) >> 0]; //changes second spot to hex
    }
}
/**
 * @brief changes binary_buffer for output
 * 
 * @param buffer pointer to buffer
 * @param len length of buffer or nr
 * @param out the binary_buffer that will be changed and outputed later
 */
void binary(char* buffer, ssize_t len, char* out)
{   
    for(int i = 0; i <= len - 1; i++) 
    {
        for (int j = 0; j < 8; j++) //loops throught for all 8 bits in each byte
        {
            out[i * 8 + j] = ((buffer[i] & (1 << (7 - j))) >> (7 - j)) + 48; //converts each bit to 0 or 1
        }
    }
}
/**
 * @brief finds min from two ints
 * 
 * @param x int 1
 * @param y int 2
 * @return ssize_t whichever is smaller
 */
ssize_t min (ssize_t x, ssize_t y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}
