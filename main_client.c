#include "header.h"

int main(int argc, char const *argv[]) {
  int Socket_perso, test_connection, i;
  struct sockaddr_in localAddr, servAddr;
  struct hostent *hote;

  if(argc < 4){ //si il n' y a pas assez d'argumebnt on arrete
    printf("usage: %s <serveur> <2 = fichier // 1 = mot> <data1> <data2> ... <dataN>\n", argv[0]);
    exit (1);
  }

  //tentative de résolution de l'hote sur lequel on cherche la connection
  hote = gethostbyname(argv[1]);
  if(hote == NULL){
    printf("%s: hôte inconnu '%s'\n", argv[0], argv[1]);
    exit(1);
  }

  //on copie les informations de l'hote dans servAddr
  servAddr.sin_family = hote->h_addrtype;
  memcpy((char *) &servAddr.sin_addr.s_addr, hote->h_addr_list[0], hote->h_length);
  servAddr.sin_port = htons(SERVER_PORT);

  //création de la socket
  Socket_perso = socket(AF_INET, SOCK_STREAM, 0);
  if(Socket_perso < 0){
    perror(" impossible de créer une socket ");
    exit(1);
  }

  //liaison de la socket au port 1500
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(0);

  //on test la connection entre la socket et le port
  test_connection = bind(Socket_perso, (struct sockaddr *) &localAddr, sizeof(localAddr));
  if(test_connection < 0){
    printf("%s: impossible de lier les ports TCP %u\n", argv[0], SERVER_PORT);
    printf("erreur ");
    exit(1);
  }

  //on testela connection au serveur
  test_connection = connect(Socket_perso, (struct sockaddr *) &servAddr, sizeof(servAddr));
  if(test_connection < 0){
    perror("impossible de se connecter ");
    exit(1);
  }

  //on regarde ce que l'on doit faire, envoyer une ou deux données ou demander un fichier
  if(strcmp(argv[2],"1") == 0) send_line(argc, argv, Socket_perso);
  else if(strcmp(argv[2],"2") == 0) ask_fic(Socket_perso, argv[3]);
  else printf("Vous n'avez pas entré 1 ou 2... ");

  //on ferme la socket
  close(Socket_perso);
  return 0;
}
