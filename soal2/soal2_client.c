#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int screen;

void screen1(int sock)
{
  char *input;
  puts("Screen 1");
  puts("1. Login");
  puts("2. Register");
  printf("Choices : ");
  scanf("%s", input);

  char *username, *password;
  printf("Username : "); scanf("%s", username);
  printf("Password : "); scanf("%s", password);
  
  send(sock, input, strlen(input), 0);
  send(sock, username, strlen(input), 0);
  send(sock, password, strlen(input), 0);
  
  char buffer[1024] = {0};
  int valread = read(sock, buffer, 1024);
  
  // terima respon server
  if(!strcmp(buffer, "Auth success"))
  {
    puts("login success");
  }

  else if (!strcmp(buffer, "register success"))
  {
    puts(buffer);
    puts("login success");
  }

  else puts("login failed");

  screen = 2;
  return;
}

void screen2(int sock)
{
  char *input;
  puts("Screen 2");
  puts("1. Find Match");
  puts("2. Logout");
  printf("Choices : ");
  scanf("%s", input);

  if (!strcmp(input, "logout") || !strcmp(input, "Logout"))
  {
    screen = 1;
    return;
  }

  if (!strcmp(input, "find") || !strcmp(input, "Find"))
  {
    // tunggu player lain

    // kalo ketemu, print “Game dimulai silahkan ​ tap ​ ​ tap ​ secepat mungkin !!”
  }

}

int main(int argc, char const *argv[])
{
  struct sockaddr_in address;
  int sock = 0, valread;
  struct sockaddr_in serv_addr;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return -1;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
      
  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
  {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\nConnection Failed \n");
    return -1;
  }


  //ini mainnya
  while (1)
  {
    if (screen == 1) screen1(sock);
    
    if (screen == 2) screen2(sock);
  }

  return 0;
}