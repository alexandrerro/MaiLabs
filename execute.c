#include <stdio.h>
#include <stdlib.h>

#include "computer.h"
#include "io.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "rb");

    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    int maxDevices = 2;

    Computer s;

    while (computerReadTxt(&s, in)) { 
        if (s.processorNumber == 2 && s.deviceNumber <= maxDevices) {
            printf("%s\n", s.surname);
        }
    }

    fclose(in);

    return 0;
}

