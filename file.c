#include "file.h"
#include "des.h"

long getFileSize(FILE* fp){
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;
}

void ecrireFichier(char *filename, uint64_t* blocs, size_t blocNumber){
    FILE* f = fopen(filename, "wb");

    char* msgChiffre = contentFromBlocs(blocs, blocNumber);
    fwrite(msgChiffre, 1, sizeof(msgChiffre), f);
    /*for(size_t i = 0; i < blocNumber; i++){
        uint64_t bloc = blocs[i];
        fwrite(&bloc, 8, 8, f);
    }
*/
    fclose(f);
}

char* lireFichier(char *filename){
    FILE *fic = fopen(filename, "r");
    if(fic == NULL){
        printf("Le fichier spécifié est vide..");
        exit(1);
    }
    long size = getFileSize(fic);
    char* content = malloc(sizeof(char) * size);

    int index = 0;
    int caract = 0;
    do{
        caract = fgetc(fic);
        content[index] = caract;
        index++;
    }while(caract != EOF);
    fclose(fic);
    return content;
}

char* contentFromBlocs(uint64_t* tabBlocs, size_t blocNumber){
    char* output = malloc(sizeof(uint64_t)* blocNumber);
    size_t n = 0;
    for(size_t i = 0; i < blocNumber; i++){
        uint64_t bloc = tabBlocs[i];
        for(size_t j = 0; j < 8; j++){
            uint64_t temp = bloc;
          
            temp >>= 64 - ((j+1) * 8);
        
            uint8_t caracter = (uint8_t)temp;
            output[n] = (char)caracter;
            n++;
        }
    }

    return output;

}