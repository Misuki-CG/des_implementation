#include <stdio.h>
#include <stdlib.h>
#include "des.h"
#include "file.h"

#define ENCODE_STRING "--encode"
#define DECODE_STRING "--decode"


void launchDecode(char* fichierEntree, uint64_t key){
    printf("\nLancement du déchiffrement avec la clé 0x%lx\n\n", key);
    size_t* tabSize = malloc(sizeof(size_t));
    size_t* msgSize = malloc(sizeof(size_t));

    uint8_t* msg = lireFichier(fichierEntree, msgSize);

    uint64_t* tabBloc = decouperBloc(msg, *msgSize, tabSize);
    
    uint64_t* blocDechif =  dechiffrement(tabBloc, *tabSize, key);
    char* msgDechif = contentFromBlocs(blocDechif, *tabSize);

    printf("Output: %s\n", msgDechif);
    free(tabBloc);
    free(tabSize);
    free(msg);
    free(msgDechif);
}

void launchEncode(char* fichierEntree, char* fichierSortie, uint64_t key){
    printf("\n Lancement du chiffrement avec le fichier %s et la clé 0x%lx\n\n", fichierEntree, key);
    size_t* tabSize = malloc(sizeof(size_t));
    size_t* msgSize = malloc(sizeof(size_t));

    uint8_t* msg = lireFichier(fichierEntree, msgSize);

    printf("Contenu du fichier : \n%s\n", msg);
    uint64_t* tabBloc = decouperBloc(msg, *msgSize, tabSize);

    uint64_t* blocChiffr = chiffrement(tabBloc, *tabSize, key);

    printf("Fin du chiffrement. Ecriture du fichier..\n");

    ecrireFichier(fichierSortie, blocChiffr, *tabSize);
    
    printf("Fin de l'écriture. Le fichier %s a été créé.\n", fichierSortie);
    free(tabBloc);
    free(tabSize);
    free(msg);
    free(blocChiffr);
}


void printUsage(){
    printf("Utilisation:\nPour déchiffrer:\n");
    printf("./main fichierEntree --decode clé\n");
    printf("Pour chiffrer : \n");
    printf("./main fichierEntree --encode clé fichierSortie\n");
}
int main(int argc, char *argv[])
{
    if(argc < 4){
        printUsage();
        return 1;
    }
    if(strcmp(argv[2], DECODE_STRING) == 0){
        
        uint64_t key;
        if(argv[3][0] == '0' && argv[3][1] == 'x'){
             key = (uint64_t)(strtol(argv[3], NULL, 0));
        }
        else{
           key = (uint64_t)(strtol(argv[3], NULL, 16));
        }
        launchDecode(argv[1], key);
    }
    else if(strcmp(argv[2], ENCODE_STRING) == 0){
        if(argc < 5){
            printUsage();
            return 1;
        }
        uint64_t key;
        if(argv[3][0] == '0' && argv[3][1] == 'x'){
             key = (uint64_t)(strtol(argv[3], NULL, 0));
        }
        else{
           key = (uint64_t)(strtol(argv[3], NULL, 16));
        }

        launchEncode(argv[1], argv[4], key);
    }
    else{
        printUsage();
    }

	
    return 0;
}