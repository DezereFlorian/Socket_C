#include "header.h"

/*fonction send_line pour envoyer des mots au serveur*/
int send_line(int nb_data, char const *data[], int sd){
  int i = 0;
  int test_envoi = 0;
  for(i = 3; i < nb_data; i++){
    test_envoi = send(sd, data[i], strlen(data[i]) + 1, 0);

    //on test l'envoi de chaque donnée
    if(test_envoi < 0){
      perror("impossible d'envoyer les data");
      exit(1);
    }

    //on affiche ce que l'on a envoyé
    printf("%s: data%u envoyé ---%s---\n", data[0], i - 2, data[i]);
  }
}

/*fonction permettant de demander au serveur d'envoyer un fichier*/
int ask_fic(int Socket, const char *nom_fic){
  printf("DEMANDE DE FICHIER....");
  //allocation de mémoire pour la reception du fichier
  char *text_recu = malloc(sizeof(char) * MAX_MSG);

  //envoie du nom du fichier donne en argument de l'execution du programme
  send(Socket, nom_fic, strlen(nom_fic) + 1, 0);
  //ouverture du fichier en ecriture
  FILE* fic = fopen(nom_fic, "w");

  //tant que on ne reçoit pas le caractère EOF on continu
  while(text_recu != "EOF"){
    recv(Socket, text_recu, MAX_MSG, 0);
    if(text_recu != "EOF") fwrite(text_recu, sizeof(char), MAX_MSG, fic);
    //on ecrit dans le fichier si ce que l'on reçoit ne vaut pas EOF
  }

  //on ferme le fichier ainsi créer
  fclose(fic);
  return 0;
}
