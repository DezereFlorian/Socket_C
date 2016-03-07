#include "header.h"

/*fonction send_line pour envoyer des mots au serveur*/
int send_line(int nb_data, char const *data[], int sd, int rc){
  int i = 0;
  for(i = 3; i < nb_data; i++){
    rc = send(sd, data[i], strlen(data[i]) + 1, 0);

    if(rc < 0){
      perror("impossible d'envoyer les data");
      exit(1);
    }

    printf("%s: data%u envoyé ---%s---\n", data[0], i - 2, data[i]);
  }
}

/*fonction permettant de demander au serveur d'envoyer un fichier*/
int ask_fic(int sd, const char *nom_fic){
  char *r = malloc(sizeof(char) * MAX_MSG);

  send(sd, nom_fic, strlen(nom_fic) + 1,0);
  FILE* fic = fopen(nom_fic, "w");

  while(r[0] =! 'EOF'){
    recv(sd, r, MAX_MSG, 0);
    if(r[0] != 'EOF') fwrite(r, sizeof(char), MAX_MSG, fic);
  }

  fclose(fic);
  return 0;
}
