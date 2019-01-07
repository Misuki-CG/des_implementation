#ifndef _setup_h
#define _setup_h

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

void lireFichier(char* nameDoc, char* resultat);
void decouperBloc(uint64_t message, uint64_t* blocs);
void f(uint64_t bloc, uint64_t* resultat);
void chiffrementBloc(uint64_t bloc);
void dechiffrementBloc(uint64_t bloc);
void partitionnerBloc(uint64_t bloc, uint32_t* blocL, uint32_t* blocR);

#endif
