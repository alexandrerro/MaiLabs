#include "computer.h"
#include "io.h"

// Этот файл отвечает только за печать

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r");

    if (argc != 2) {
        printf("Usage:\n\t./print DB_FILE\n");
        exit(0);
    }

    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    Computer s;

    while (computerReadTxt(&s, in)) {
        computerPrint(&s); 
    }

    fclose(in);

    return 0;
}
