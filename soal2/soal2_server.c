#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#define PORT 8080

void *createFile(void *arg)
{
  puts("masuk createFile");

  char *filename = "akun.txt";
  char *permission = "a";
  DIR *d_work;
  struct dirent *dir_work;
  d_work = opendir(".");

  while ((dir_work = readdir(d_work)) != NULL)
  {
    if (!strcmp(filename, dir_work->d_name))
    {
      puts("file exist");
      permission = "a+";
      break;
    }
  }

  FILE * fPtr;
  fPtr = fopen(filename, permission);

  /* fopen() return NULL if last operation was unsuccessful */
  if(fPtr == NULL)
  {
    /* File not created hence exit */
    puts("Failed to create file.");
    exit(EXIT_FAILURE);
  }
}

pthread_t thread1;

int main(int argc, char const *argv[])
{
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
    
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
    
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons( PORT );
    
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  //ini mainnya
  int err;
  err = pthread_create(&(thread1),NULL,&createFile,NULL);
  if(err!=0) //cek error
  {
    printf("\n can't create thread : [%s]",strerror(err));
  }
  else
  {
    printf("\n create thread success\n");
  }

  pthread_join(thread1,NULL);

  char input[1024] = {0};
  char username[1024] = {0};
  char password[1024] = {0};

  while (1)
  {
    // terima dari client
    int read1 = read(new_socket, input, 1024);
    int read2 = read(new_socket, username, 1024);
    int read3 = read(new_socket, password, 1024);
    
    if(!strcmp(input, "login") || !strcmp(input, "Login"))
    {
      
    }
    // if berhasil login “Auth success”
    // else “Auth Failed”

    // if sukses register print username dan pass semua akun
    

  }

  return 0;
}