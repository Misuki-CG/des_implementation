#ifndef _setup_h
#define _setup_h

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

uint8_t getBitValue(uint64_t bloc, uint64_t position);
void setbitvalue(uint64_t* v, uint8_t idx, uint8_t value);
void print_bits(int size, uint64_t x);
long f(int i);
uint64_t expansion(uint32_t subBloc);
int8_t getNumberOfShift(size_t tour);
void shiftBlocs(uint32_t* blocC, uint32_t* blocD,  uint8_t numberOfShift);
void makeKeys(uint32_t blocC, uint32_t blocD);
void initKey(uint64_t k);
void partitionBloc(uint64_t bloc, uint32_t* blocL, uint32_t* blocR);
uint32_t appliquerSBoxes(uint64_t blocOf48);
uint32_t fFunction(uint32_t bloc, size_t tour);
uint64_t permutation(uint64_t bloc, int* permutation);
void permuterBlocs(uint64_t* bloc);
uint64_t dechiffrementBloc(uint64_t bloc, size_t tour);
uint64_t chiffrementBloc(uint64_t bloc, size_t tour);
uint64_t* chiffrement(uint64_t* b, size_t blocNumber, uint64_t key);
uint64_t* dechiffrement(uint64_t* b, size_t blocNumber, uint64_t key);
int desMain();
uint64_t* decouperBloc(char* message, size_t* size);
#endif
 