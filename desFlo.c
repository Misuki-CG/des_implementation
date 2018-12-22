#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

/*



*/
void print_bits(int size, uint64_t x)
{
	uint8_t bit;
	printf("0b");
	for(int j=size-1; j>=0; j--) {
		for(int i=7; i>=0; i--) {
			bit=x>>(i+j*8) & 1;
			printf("%d",bit);
		}
		printf(" ");
	}
	printf("\n");
}

// La permutation finale avant sortie de f

int P[32]={
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25};

// permutation initiale (IP) 
int PI[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7};

// permutation inverse (IP-1)
int PI_INV[64] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25};


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

uint8_t getBitValue(uint64_t bloc, uint64_t position){
    return (bloc >> position) & 0x00000001;
}
void setbitvalue(uint64_t* v, uint8_t idx, uint8_t value)
{
	if (value == 0ul)
		*v = *v & ~(1ul << idx);
	else
		*v = *v | (1ul << idx);
}

uint64_t permutation(uint64_t bloc, int* permutation){
    uint64_t blocPermu = 0ul;
    printf("====\n");

    printf("Permutation du bloc 0x%lx\n", bloc);

    for(size_t i = 0; i < 64; i++){
        uint64_t index = permutation[i];
        uint8_t bitValue = getBitValue(bloc, 64-index);
    
        // donc là j'ai potentiellement 00000001 ou 00000000
        // que je veux mettre à l'index i de mon blocPermu
        setbitvalue(&blocPermu, (uint64_t)(63-i), bitValue);

    }
    printf("Fin de la permutation : 0x%lx\n", blocPermu);
    printf("====\n");

    return blocPermu;
}



// Échange les 32 premiers bits de positions avec les 32 derniers 
// (échange de place les deux sous-blocs contenu dans le bloc passé en paramètre)
void permuterBlocs(uint64_t* bloc){

    uint32_t* blocL = malloc(sizeof(uint32_t));
    uint32_t* blocR = malloc(sizeof(uint32_t));
    partitionBloc(*bloc, blocL, blocR);

    *bloc = *blocR;
    *bloc = *bloc << 32;
    *bloc += *blocL;

}

// Déchiffrement d'un bloc de 64 bits
uint64_t dechiffrementBloc(uint64_t bloc, size_t tour){
    uint64_t blocDechiffre;
    uint32_t* blocL = malloc(sizeof(uint32_t));
    uint32_t* blocR = malloc(sizeof(uint32_t));

    partitionBloc(bloc, blocL, blocR);

    blocDechiffre = *blocR ^ f(tour); // bloc de gauche
    blocDechiffre <<= 32; // on met le bloc de gauche à gauche
    blocDechiffre += *blocL; // bloc de droite

    return blocDechiffre;
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
    printf("===== chiffrement =====\n");

    b = permutation(b, PI);
    for(size_t i = 0; i < 16; i++){
        b = chiffrementBloc(b, i);
        printf("%d. 0x%lx\n", (int)i, b);
    }

    // Echange des deux blocs droite => gauche et gauche => droite
    permuterBlocs(&b);

    // Application de la permutation inverse IP-1
    b = permutation(b, PI_INV);

    printf("Res: \n(Res:)0x%lx\n(Att:)0xa2b3aab7202ef6e7\n", b);

    


    /* ===== Déchiffrement ===== */
   /*  printf("===== dechiffrement =====\n");
    permuterBlocs(&b);
    for(int i = 15; i >= 0; i--){
        b = dechiffrementBloc(b, i);
        printf("%d. 0x%lx\n", (int)i, b);
    }

   

    printf("Res: \n(Res:)0x%lx\n(Att:)0x123456789abcdef\n", b);
   */ 

}