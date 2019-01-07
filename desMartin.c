#include "des.h"

/*uint8_t getbitvalue(uint8_t v, uint8_t idx){
  return (v >> idx) & 1;
}

void lireFichier(char* nameDoc, char* resultat){
  FILE* f = fopen(nameDoc, "r");
  fseek(f, 0, SEEK_END);
  long int size = ftell(f);
  printf("size : %ld \n", size);
  rewind(f);
  uint8_t* fm = calloc(size, 1);
  fread(fm, 1, size, f);
  for( uint32_t i = 0; i < size; i++){
    printbits_8(fm[i]);
    printf(" ");
  }
  printf("\n");
}

void printbits_8(uint8_t v)
{
  for(uint8_t i = 8; i > 0; i--)
  {
    printf("%u", getbitvalue(v, i-1));
  }
}*/

void lireFichier (char* nameDoc, char* resultat){
  FILE *fic = fopen(nameDoc, "r");
  signed char texte[256];


  if (fic == NULL){
    exit(1);
  }

  while(fgets(texte, 255, fic) != NULL){
    resultat += texte;
    printf("test\n");
    printf("%s\n", resultat);
  }

  fclose(fic);

  return 0;
}
