#include "header.h"

/*function readline permettant de lire une ligne d'un fichier*/
int read_line (int newSd, char *line_to_return){
  static int rcv_ptr = 0;
  static char rcv_msg[MAX_MSG];
  static int n = 0;
  int offset = 0;

  while (1){
    if (rcv_ptr == 0){ //lecture de data depuis la socket
      memset(rcv_msg, 0x0, MAX_MSG); //initialisation du buffer
      n = recv(newSd, rcv_msg, MAX_MSG, 0); //attente des datas
      if (n < 0){
        perror(" ne peut recevoir de data ");
        return ERROR;
      } else if (n == 0){
        printf(" le client à stopper la connection\n");
        close(newSd);
        return ERROR;
      }
    }

    //si data lu sur la socket ou si une autre ligne est dans le buffer
    while(*(rcv_msg + rcv_ptr ) != END_LINE && rcv_ptr < n){
      memcpy(line_to_return + offset, rcv_msg + rcv_ptr, 1);
      offset++;
      rcv_ptr++;
    }

    //fin de ligne et fin de buffer => alors retour a la ligne
    if(rcv_ptr == n-1){
      *(line_to_return + offset) = END_LINE; //on met le dernier octet à END_LINE
      rcv_ptr = 0;
      return ++offset;
    }

    //fin de la ligne mais encore des données dans le buffer => alors retour a la ligne
    if(rcv_ptr < n-1){
      *(line_to_return + offset) = END_LINE; //on met le dernier octet à END_LINE
      rcv_ptr++;
      return ++offset;
    }

    //fin du buffer mais ligne non fini, on attend que plus de data arrive sur la socket
    if(rcv_ptr == n){
      rcv_ptr = 0;
    }
  } //fin du while
}
