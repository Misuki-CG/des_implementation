#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

uint8_t* lireFichier(char* fileName, size_t* fileSize);
char* contentFromBlocs(uint64_t* tabBlocs, size_t blocNumber);
void ecrireFichier(char *filename,  uint64_t* blocs, size_t blocNumber);
long getFileSize(FILE* fp);