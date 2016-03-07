#include "header.h"

int main(int argc, char const *argv[]) {
  int sd, rc, i;
  struct sockaddr_in localAddr, servAddr;
  struct hostent *h;

  if(argc < 4){
    printf("usage: %s <serveur> <2 = fichier // 1 = mot> <data1> <data2> ... <dataN>\n", argv[0]);
    exit (1);
  }

  //h = char *inet_aton(const char *sadr, struct in_addr *addr);
  h = gethostbyname(argv[1]);
  if(h == NULL){
    printf("%s: hôte inconnu '%s'\n", argv[0], argv[1]);
    exit(1);
  }

  servAddr.sin_family = h->h_addrtype;
  memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  servAddr.sin_port = htons(SERVER_PORT);

  //création de la socket
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd < 0){
    perror(" impossible de créer une socket ");
    exit(1);
  }

  //liaison à n'importe quelle port
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(0);

  rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
  if(rc < 0){
    printf("%s: impossible de lier les ports TCP %u\n", argv[0], SERVER_PORT);
    printf("erreur ");
    exit(1);
  }

  //connection au serveur
  rc = connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
  if(rc < 0){
    perror("impossible de se connecter ");
    exit(1);
  }

  if(strcmp(argv[2],"1") == 0) send_line(argc, argv, sd, rc);
  else if(strcmp(argv[2],"2") == 0) ask_fic(sd, argv[3]);
  else printf("Vous n'avez pas entré 1 ou 2... ");
  
  close(sd);
  return 0;
}
