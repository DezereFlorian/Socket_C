#include "header.h"

/*fonction readline permettant de lire une ligne d'un fichier*/
int read_line (int Socket_client, char *output_line){
  static int donnee_restante = 0;
  static char message_recu[MAX_MSG];
  static int test_reception = 0;
  int offset = 0;

  while (1){
    if (donnee_restante == 0){ //lecture de data depuis la socket
      memset(message_recu, 0x0, MAX_MSG); //initialisation du buffer
      test_reception = recv(Socket_client, message_recu, MAX_MSG, 0); //attente des datas
      if (test_reception < 0){
        perror(" ne peut recevoir de data ");
        return ERROR;
      } else if (test_reception == 0){
        printf(" le client à stopper la connection\n");
        close(Socket_client);
        return ERROR;
      }
    }

    //si data lu sur la socket ou si une autre ligne est dans le buffer
    while(*(message_recu + donnee_restante ) != END_LINE && donnee_restante < test_reception){
      memcpy(output_line + offset, message_recu + donnee_restante, 1);
      offset++;
      donnee_restante++;
    }

    //fin de ligne et fin de buffer => alors retour a la ligne
    if(donnee_restante == test_reception-1){
      *(output_line + offset) = END_LINE; //on met le dernier octet à END_LINE
      donnee_restante = 0;
      return ++offset;
    }

    //fin de la ligne mais encore des données dans le buffer => alors retour a la ligne
    if(donnee_restante < test_reception-1){
      *(output_line + offset) = END_LINE; //on met le dernier octet à END_LINE
      donnee_restante++;
      return ++offset;
    }

    //fin du buffer mais ligne non fini, on attend que plus de data arrive sur la socket
    if(donnee_restante == test_reception){
      donnee_restante = 0;
    }
  } //fin du while
}

//fonction permettant au serveur d'envoyer un fichier depuis un nom
int lecture_fic(int socket_client){
  char* ln = malloc(sizeof(char) * MAX_MSG);
  char* nom_fic;
  int longueur_data_send = 0; //longueur de la data qui sera envoyé

  recv(socket_client, nom_fic, strlen(nom_fic) + 1, 0);
  FILE* fic = fopen(nom_fic, "r");
  printf("lqdfbgùgjerq,o*gqerpgjmrgjr*,rgjp");

  while(!feof(fic)){
    longueur_data_send = fread(ln, sizeof(char), MAX_MSG, 0);
    send(socket_client, ln, longueur_data_send+1, 0);
  }
  send(socket_client, "EOF", 1, 0);
  fclose(fic);
}
