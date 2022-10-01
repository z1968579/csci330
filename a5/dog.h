#ifndef DOG_H
#define DOG_H
/**
 * @file dog.h
 * @author Jacob Rudawski z1968579
 * @brief CSCI 330 Assignment 5
 * @date 10/03/2022
 */
//char* buffer and buffer length
#include <sys/types.h> 
#define SIZE_BUFFER 4096

void caesar(char*, ssize_t, ssize_t);
void byte(char*, ssize_t, ssize_t);
void hex(char*, ssize_t);
void binary(char*, ssize_t);
ssize_t min(ssize_t,ssize_t);

#endif