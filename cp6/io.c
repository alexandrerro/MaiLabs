#include "computer.h"
#include "io.h"

/* Computer IO */
int computerReadTxt(Computer *s, FILE *in)
{
    fscanf(in, "%s", s->surname);
    fscanf(in, "%d", &(s->processorNumber));
    fscanf(in, "%s", s->processorType);
    fscanf(in, "%d", &(s->memorySize));
    fscanf(in, "%s", s->videoControllerType);
    fscanf(in, "%d", &(s->videoMemorySize));
    fscanf(in, "%s", s->diskType);
    fscanf(in, "%d", &(s->diskNumber));
    fscanf(in, "%d", &(s->diskCapacity));
    fscanf(in, "%d", &(s->intcontrNumber));
    fscanf(in, "%d", &(s->deviceNumber));
    fscanf(in, "%s", s->os);
    return !feof(in);
}


void computerPrint(Computer *s)
{
    printf("Name: %s\n", s->surname);
    printf("Processor Number: %d\n", s->processorNumber);
    printf("Processor Type: %s\n", s->processorType);
    printf("Memory Size: %d\n", s->memorySize);
    printf("video Controller Type: %s\n", s->videoControllerType);
    printf("video Memory Size: %d\n", s->videoMemorySize);
    printf("Disk Type: %s\n", s->diskType);
    printf("Disk Number: %d\n", s->diskNumber);
    printf("Disk capacity: %d\n", s->diskCapacity);
    printf("Integretad controllers number: %d\n", s->intcontrNumber);
    printf("Contr Number: %d\n", s->deviceNumber);
    printf("OS: %s\n", s->os);
    printf("\n"); 
}

 int computerReadBin(Computer *s, FILE *in)
{
    fread(&(s->surname),  sizeof(char), STR_SIZE, in);
    fread(&(s->processorNumber), sizeof(int), 1, in);
    fread(&(s->processorType), sizeof(char), STR_SIZE, in);
    fread(&(s->memorySize), sizeof(int), 1, in);
    fread(&(s->videoControllerType), sizeof(char), STR_SIZE, in);
    fread(&(s->videoMemorySize), sizeof(int), 1, in);
    fread(&(s->diskType), sizeof(char), STR_SIZE, in);
    fread(&(s->diskNumber), sizeof(int), 1, in);
    fread(&(s->diskCapacity), sizeof(int), 1, in);
    fread(&(s->intcontrNumber), sizeof(int), 1, in);
    fread(&(s->deviceNumber), sizeof(int), 1, in);
    fread(&(s->os), sizeof(char), STR_SIZE, in);
    return !feof(in);
}
 

void computerWriteBin(Computer *s, FILE *out) {
    fwrite(&(s->surname),  sizeof(char), STR_SIZE, out);
    fwrite(&(s->processorNumber), sizeof(int), 1, out);
    fwrite(&(s->processorType), sizeof(char), STR_SIZE, out);
    fwrite(&(s->memorySize), sizeof(int), 1, out);
    fwrite(&(s->videoControllerType), sizeof(char), STR_SIZE, out);
    fwrite(&(s->videoMemorySize), sizeof(int), 1, out);
    fwrite(&(s->diskType), sizeof(char), STR_SIZE, out);
    fwrite(&(s->diskNumber), sizeof(int), 1, out);
    fwrite(&(s->diskCapacity), sizeof(int), 1, out);
    fwrite(&(s->intcontrNumber), sizeof(int), 1, out);
    fwrite(&(s->deviceNumber), sizeof(int), 1, out);
    fwrite(&(s->os), sizeof(char), STR_SIZE, out);
}
