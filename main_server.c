#include "header.h"

int main(int argc, char const *argv[]) {
  int Socket_server, Socket_client, cliLen;

  struct sockaddr_in cliAddr, servAddr;
  char line[MAX_MSG];

  //création de la socket du server
  Socket_server = socket(AF_INET, SOCK_STREAM, 0);
  if(Socket_server < 0){
    perror(" impossible d'ouvrir une socket ");
    return ERROR;
  }

  //Recopie des paramètres de la socket dans la variable serAddr
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(SERVER_PORT);

  //test de liaison entre le port 1500 et la socket du server
  if(bind(Socket_server, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0){
    perror(" impossible de lier un port ");
    return ERROR;
  }

  listen(Socket_server, 5); //reservation d'un peu de memoire --> action inutile dans notre configuration

  while(1){
    //on se met en attente de data a recuperer
    printf("%s, attente de data sur le port %u\n", argv[0], SERVER_PORT);

    //on attend une demande de connection d'une socket extérieur
    cliLen = sizeof(cliAddr);
    Socket_client = accept(Socket_server, (struct sockaddr *) &cliAddr, &cliLen);

    //on vérifie que la connexction peut se faire
    if(Socket_client < 0){
      perror(" impossible d'accepter la connection ");
      return ERROR;
    }

    //on remplit la variable line avec des 0
    //memset(line, 0x0, MAX_MSG);

    //cas d'une réception de data style "mots"
    // while(read_line(Socket_client, line) != ERROR){
    //   printf("%s: reçu de %s: TCP%d : %s\n", argv[0], inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line);
    //   memset(line, 0x0, MAX_MSG); //initialisation de la ligne
    // }
    //cas d'une réception de data style demande de transfert de fichier
    lecture_fic(Socket_client);
  }
}
