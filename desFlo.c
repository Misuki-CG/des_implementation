#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

/*



*/

// découpe le message en bloc de 64 bits
uint64_t* decouperBloc(char* message){
    return 0;
}

// Fonction f(i)
long f(int i){
    return i * 37453123;
}

// Partitionne un bloc de 64 bits en deux blocs de 32 bits (bloc de droite & bloc de gauche)
void partitionBloc(uint64_t bloc, uint32_t* blocL, uint32_t* blocR){

    // on récupère le bloc de droite (les 32 "derniers" bits)
    *blocR = (uint32_t)bloc; 
    // on écrase le bloc de droite par le bloc de gauche en shiftant les bits
    bloc = bloc >> 32;
    // on récupère le bloc de droite (devenu bloc de gauche)
    *blocL = (uint32_t)bloc;

}

// Chiffre un bloc de 64 bits
uint64_t chiffrementBloc(uint64_t bloc, size_t tour){

    uint64_t blocChiffre;
    uint32_t* blocL = malloc(sizeof(uint32_t));
    uint32_t* blocR = malloc(sizeof(uint32_t));
    
    // Découpage du bloc de 64 bits en 2 blocs de 32 bits
    partitionBloc(bloc, blocL, blocR);

    blocChiffre = *blocR; // nouveau bloc de gauche 
    blocChiffre = blocChiffre << 32;

    long fResult = f(tour);

    blocChiffre += *blocL ^ fResult; // nouveau bloc de droite
    
    return blocChiffre;

}


int main(int argc, char *argv[]){

    uint64_t b = 0x0123456789abcdef;

    printf("0x%lx\n", b);

    for(size_t i = 0; i < 16; i++){
        b = chiffrementBloc(b, i);
        printf("%d. 0x%lx\n", i, b);
    }
    // TODO: Echange des deux blocs droite => gauche et gauche => droite
    uint32_t* blocL = malloc(sizeof(uint32_t));
    uint32_t* blocR = malloc(sizeof(uint32_t));
    partitionBloc(b, blocL, blocR);

    b = *blocR;
    b = b << 32;
    b += *blocL;

    
    printf("Res: \n(Res:)0x%lx\n(Att:)0xb94bd5cf02dcad77\n", b);

    

    

}