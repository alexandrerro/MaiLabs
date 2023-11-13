#ifndef computer_h
#define computer_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 50

typedef struct
{
    char surname[STR_SIZE];
    int processorNumber;
    char processorType[STR_SIZE];
    int memorySize;
    char videoControllerType[STR_SIZE];
    int videoMemorySize;
    char diskType[STR_SIZE];
    int diskNumber;
    int diskCapacity;
    int intcontrNumber;
    int deviceNumber;
    char os[STR_SIZE];
} Computer;

#endif



