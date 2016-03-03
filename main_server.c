#include "header.h"

int main(int argc, char const *argv[]) {
  int sd, newSd, cliLen;

  struct sockaddr_in cliAddr, servAddr;
  char line[MAX_MSG];

  //création de la socket
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd < 0){
    perror(" impossible d'ouvrir une socket ");
    return ERROR;
  }

  //Association des ports au serveur
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(SERVER_PORT);

  if(bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0){
    perror(" impossible de lier un port ");
    return ERROR;
  }

  listen(sd, 5); //reservation d'un peu de memoire, mais inutile

  while(1){
    printf("%s, attente de data sur le port %u\n", argv[0], SERVER_PORT);

    cliLen = sizeof(cliAddr);
    newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
    if(newSd < 0){
      perror(" impossible d'accepter la connection ");
      return ERROR;
    }

    memset(line, 0x0, MAX_MSG); //initialisation de la ligne

    //reception de segment
    while(read_line(newSd, line) != ERROR){
      printf("%s: reçu de %s: TCP%d : %s\n", argv[0], inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line);
      memset(line, 0x0, MAX_MSG); //initialisation de la ligne
    }
  }
}
