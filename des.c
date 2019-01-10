#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>


const uint64_t K = 0x123456789abcdef;
const uint64_t K1 = 0x1B02EFFC7072;

uint64_t keys[16] = {0,0,0,0,
                    0,0,0,0,
                    0,0,0,0,
                    0,0,0,0};
/*



*/


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

// matrice d'expansion
int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Les S-Boxes
int SBOX[8][4][16] = {
    {
        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
    },
    
    {
        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
    },
    
    {
        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
        {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
    },
    
    {
        { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
        {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
        {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
        { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
    },
    
    {
        { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
        {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
        { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
        {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
    },
    
    {
        {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
        {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
        { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
        { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
    },
    
    {
        { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
        {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
        { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
        { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
    },
    
    {
        {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
        { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
        { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
        { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
    },
    
};
// choix permut� dans la diversification de la cl�

int PC1[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4};

int PC2[48]={
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32};

// retourne l'état du bit demandé (1 ou 0)
uint8_t getBitValue(uint64_t bloc, uint64_t position){
    return (bloc >> position) & 0x00000001;
}


// change la valeur du bit demandé avec la valeur demandée
void setbitvalue(uint64_t* v, uint8_t idx, uint8_t value)
{
	if (value == 0ul)
		*v = *v & ~(1ul << idx);
	else
		*v = *v | (1ul << idx);
}



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
uint64_t* decouperBloc(uint8_t* message, size_t messageSize, size_t* size){
    size_t longueur = messageSize;
    size_t nbrBloc = 0;
    size_t n = 0;
    uint8_t lettre;

    nbrBloc = longueur%8 == 0 ? longueur / 8 : (longueur / 8) + 1;
    *size = nbrBloc;
    uint64_t* tabOutput = malloc(sizeof(uint64_t) * nbrBloc);
    for(size_t i = 0; i < nbrBloc; i++){
        for(size_t j = 0; j < 8; j++){
            
            if(n > longueur){
                i = nbrBloc;
                break;
            }
            uint64_t blocTemp = 0x0;
            lettre = message[n];
            blocTemp = lettre;
            blocTemp <<= 64-(8*(j+1));
            tabOutput[i] += blocTemp;

            n++;
        }
        printf("bloc %ld : ", i == nbrBloc ? i-1 : i);
        print_bits(8,tabOutput[i == nbrBloc ? i-1 : i]);
    }

    return tabOutput;
}

// Fonction f(i)
long f(int i){
    return i * 37453123;
}

uint64_t expansion(uint32_t subBloc){


    uint64_t blocExpansion = 0ul;
    for(size_t i = 0; i < 48; i++){
        uint64_t index = E[i];
        uint8_t bitValue = getBitValue(subBloc, 32-index);

        setbitvalue(&blocExpansion, (uint64_t)(47-i), bitValue);
    }

    return blocExpansion;
}

int8_t getNumberOfShift(size_t tour){
    if(tour == 0 || tour == 1 || tour == 8 || tour == 15){
        return 1;
    }

    return 2;
}

void shiftBlocs(uint32_t* blocC, uint32_t* blocD,  uint8_t numberOfShift)
{
    for(size_t i = 0; i < numberOfShift; i++){
        uint8_t firstBitC = getBitValue(*blocC, 31);
        uint8_t firstBitD = getBitValue(*blocD, 31);

        *blocC <<= 1;
        *blocD <<= 1;

        setbitvalue((uint64_t*)blocC, 4, firstBitC);
        setbitvalue((uint64_t*)blocD, 4, firstBitD);


    }
}

void makeKeys(uint32_t blocC, uint32_t blocD){
    // les 4 derniers bits des deux blocs ne servent à rien

    uint32_t nextC = blocC;
    uint32_t nextD = blocD;

    
    for(size_t i = 0; i < 16; i++){
        // shift
        uint8_t shiftLength = getNumberOfShift(i);
        shiftBlocs(&nextC, &nextD, shiftLength);
        
        /*
        printf("c%ld (0x%x) ", i+1, nextC);
        print_bits(4, nextC);
        printf("d%ld (0x%x) ", i+1, nextD);
        print_bits(4, nextD);
        */
        // création du bloc concaténé 
        uint64_t concatKey = nextC;
        concatKey <<= 32;
        uint64_t tempD = nextD;
        tempD <<= 4;
        concatKey += tempD;

        /*
        printf("concatKey (0x%lx) ", concatKey);
        print_bits(8, concatKey);
        */
        // permutation PC2
        uint64_t iKey = 0x0;
        for(size_t j = 0; j < 48; j++){
            uint64_t index = PC2[j];
            uint8_t bitValue = getBitValue(concatKey, 64-index);
            setbitvalue(&iKey, (uint64_t)(47-j), bitValue);
        }



        keys[i] = iKey;
    }
    
}


void initKey(uint64_t k){
   
    //printf("k : (0x%lx) ", k);
    //print_bits(8, k);
    uint64_t KPerm = 0x0;
    for(size_t i = 0; i < 56; i++){
        uint64_t index = PC1[i];
        uint8_t bitValue = getBitValue(k, 64-index);

        setbitvalue(&KPerm, (uint64_t)(63-i), bitValue);
    }
    //printf("initKey : (0x%lx) " , KPerm);
    //print_bits(8, KPerm);

    
    // split en deux bloc de la clé
    
    KPerm >>= 8;
    uint32_t d0 = (uint32_t)KPerm;
    d0 <<= 4; 
    KPerm >>= 24;
    uint32_t c0 = (uint32_t)KPerm;

    // les 4 derniers bits ne serviront à rien, on les mets à
    // 0 pour être sûr

    uint64_t mask = 0xffffffff0;
    c0 &= mask;
    d0 &= mask;
    /*printf("c0 : ");
    print_bits(4, c0);
    printf("d0 : ");
    print_bits(4, d0);
    */

    makeKeys(c0, d0);
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


// application des SBox sur un bloc de 48 bits
uint32_t appliquerSBoxes(uint64_t blocOf48){
    
    uint32_t blocSubstituer = 0u;

    for(size_t i = 0; i < 8; i++){ 
        // i : index de la S-Boxe à utiliser
        // index : index du premier bit de traitement
        int index = (i * 6);
        // masque qui permet de récupérer les blocs de 6 bits 
        // consécutivement (dans le sens left->right)
        uint64_t maskBloc6 = ((1ul << 6ul) - 1ul) << (42 - index);

        // on applique le masque et on décale tout sur l'octet de
        // droite
        uint8_t bloc6 = (blocOf48 & maskBloc6) >> (42 - (i * 6));

        // on calcul la position iBox avec le premier bit
        // et le dernier bit du bloc de 6 bits
        uint8_t iBox = 0u; 
        setbitvalue((uint64_t*)&iBox, (uint8_t)1, getBitValue(bloc6, (uint64_t)5));
        setbitvalue((uint64_t*)&iBox, (uint8_t)0, getBitValue(bloc6, (uint64_t)0));

        // on calcul la position jBox avec les 4 bits non traités
        // restant du bloc de 6 bits
        uint8_t jBox = 0u; 
        setbitvalue((uint64_t*)&jBox, (uint8_t)3, getBitValue(bloc6, (uint64_t)4));
        setbitvalue((uint64_t*)&jBox, (uint8_t)2, getBitValue(bloc6, (uint64_t)3));
        setbitvalue((uint64_t*)&jBox, (uint8_t)1, getBitValue(bloc6, (uint64_t)2));
        setbitvalue((uint64_t*)&jBox, (uint8_t)0, getBitValue(bloc6, (uint64_t)1));


        // on crée le bloc de 4 bits de sortie 
        uint8_t sBoxResult = SBOX[i][iBox][jBox];

        blocSubstituer += sBoxResult;

        if(i < 7)
            blocSubstituer <<= 4;


    }

    return blocSubstituer;
}

uint32_t fFunction(uint32_t bloc, size_t tour){

    uint32_t cipherBloc = 0u;
    uint64_t blocExpans = expansion(bloc);
    blocExpans = blocExpans ^ keys[tour];
    uint32_t inputToPermutation = appliquerSBoxes(blocExpans);

    for(size_t i = 0; i < 32; i++){
        uint64_t index = P[i];
        uint8_t bitValue = getBitValue(inputToPermutation, 32-index);

        setbitvalue((uint64_t*)&cipherBloc, (uint8_t)(31-i), bitValue);
    }

   
    return cipherBloc;
}

// Retourne un noubeau bloc selon la permutation décrite dans 
// le tableau de position permutation. 
uint64_t permutation(uint64_t bloc, int* permutation){
    uint64_t blocPermu = 0ul;
    

    for(size_t i = 0; i < 64; i++){
        uint64_t index = permutation[i];
        uint8_t bitValue = getBitValue(bloc, 64-index);
    
        // donc là j'ai potentiellement 00000001 ou 00000000
        // que je veux mettre à l'index i de mon blocPermu
        setbitvalue(&blocPermu, (uint8_t)(63-i), bitValue);

    }


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

    blocDechiffre = *blocR ^ fFunction(*blocL, tour); // bloc de gauche
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

    uint32_t fResult = fFunction(*blocR, tour);
    //long fResult = f(tour);
    blocChiffre += *blocL ^ fResult; // nouveau bloc de droite
    
    return blocChiffre;

}

uint64_t* chiffrement(uint64_t* b, size_t blocNumber, uint64_t key){
    
    uint64_t* blocChiffre = malloc(sizeof(uint64_t)*blocNumber);
    printf("===== chiffrement =====\n");
    for(size_t i = 0; i < blocNumber; i++){
        uint64_t iBloc = b[i];
        initKey(key);
        iBloc = permutation(iBloc, PI);
        for(size_t j = 0; j < 16; j++){
            iBloc = chiffrementBloc(iBloc, j);
        }

        // Echange des deux blocs droite => gauche et gauche => droite
        permuterBlocs(&iBloc);
        // Application de la permutation inverse IP-1
        iBloc = permutation(iBloc, PI_INV);

        blocChiffre[i] = iBloc;
    }
   
    return blocChiffre;


}

uint64_t* dechiffrement(uint64_t* b, size_t blocNumber, uint64_t key){
  /* ===== Déchiffrement ===== */
    uint64_t* blocDechiffre = malloc(sizeof(uint64_t)*blocNumber);

    printf("===== dechiffrement =====\n");

    for(size_t i = 0; i < blocNumber; i++){
        uint64_t iBloc = b[i];
        initKey(key);
        iBloc = permutation(iBloc, PI);
        permuterBlocs(&iBloc);
        for(int8_t j = 15; j >= 0; j--){
            iBloc = dechiffrementBloc(iBloc, j);
        }
        iBloc=permutation(iBloc, PI_INV);

        blocDechiffre[i] = iBloc;
    }
    

   

    return blocDechiffre;
}
