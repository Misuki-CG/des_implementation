#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>


/*void lireFichier (char* test, char* res){
  FILE *fic = fopen(test, "r");
  signed char[] texte[256];


  if (fic == NULL){
    exit(1);
  }

  while(fgets(texte, 255, fic) != NULL){
    res = strcat(res, texte);
  }

  fclose(fic);
}*/

uint64_t* decouperBloc(char* message){
  int longueur = strlen(message);
  int nbrBloc = 0;
  int n = 0;
  uint8_t lettre;
  if(longueur%8 == 0){
    nbrBloc = longueur / 8;
  }
  else{
    nbrBloc = (longueur / 8) + 1;
  }

  uint64_t* tabMess = malloc(sizeof(uint64_t) * nbrBloc);
  for(int i = 0; i < nbrBloc; i++)
  {
    for(int y = 0; y < 8; y++){
      if(n > longueur){
        i = nbrBloc;
        break;
      }
      lettre = (uint8_t) message[n];
      tabMess[i] += lettre;
      tabMess[i] <<= 64-(8*(y+1));
      n++;
    }
  }
  return tabMess;
}

void lireFichier (char* test, char* res){
  printf("message = %s\n", test);
  /*size_t i = 0;
  while(test[i] != '\0'){
    res[i] = test[i];
    printf("boucle : %c\n", res[i]);
    i++;
  }*/
  FILE *fic = fopen(test, "r");
  char texte[256];

  if(fic == NULL){
    printf("Le txt est vide\n");
    exit(1);
  }

  while(fgets(texte, 255, fic) != NULL)
  {
    printf("%s\n", texte);
  }
  res = texte;
  fclose(fic);
}
