# SoalShiftSISOP20_modul3_F01

## directory soal
- [Soal 1](soal1/)
- [Soal 2](soal2/)
- [Soal 3](soal3/)
- [Soal 4](soal4/)

## Soal no. 1



### [Source code : soal1.c](soal1)

### PENJELASAN


## Soal no. 2


### [Source code : soal2](soal2)


### PENJELASAN
untuk soal nomor 2 belum dapat diselesaikan sepenuhnya dikarenakan waktu yang tidak memungkinkan
- server side
```c
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
```

- client side
```c
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
```


## Soal no. 3


### [Source code : soal3.c](soal3/soal3.c)


### PENJELASAN



## Soal no. 4


### [Source code : soal4](soal4)


### PENJELASAN
- 4a adalah program untuk menghitung perkalian matriks menggunakan thread seperti latihan kemarin
```c
#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 

void *mult(void* arg) 
{ 
  int *data = (int *)arg; 
  int k = 0, i = 0; 

  int x = data[0]; 
  for (i = 1; i <= x; i++)
    k += data[i]*data[i+x]; 

  int *p = (int*)malloc(sizeof(int)); 
  *p = k; 

  pthread_exit(p); 
} 

int main() 
{ 
  int matA[4][2] = { {1,  20 },
                     {4,  17 },
                     {7,  8 },
                     {1,  12 } };
  int matB[2][5] = { { 1,  3,  2,  14,  9 },
                     {19,  2, 16,  13,  1 } };

  int r1=4;
  int c1=2;
  int r2=2;
  int c2=5;
  int i,j,k; 
  int val = 1;

  printf("First Matrix:\n");
  for (i = 0; i < r1; i++){ 
    for(j = 0; j < c1; j++) 
     printf("%-2d ",matA[i][j]); 
    printf("\n"); 
  } 

  printf("Second Matrix:\n");
  for (i = 0; i < r2; i++){ 
    for(j = 0; j < c2; j++) 
      printf("%-2d ",matB[i][j]); 
    printf("\n");     
  } 

  int max = r1*c2; 

  pthread_t *threads; 
  threads = (pthread_t*)malloc(max*sizeof(pthread_t)); 

  int count = 0; 
  int* data = NULL; 
  for (i = 0; i < r1; i++) 
    for (j = 0; j < c2; j++) 
    { 
      data = (int *)malloc((20)*sizeof(int)); 
      data[0] = c1; 

      for (k = 0; k < c1; k++) 
      data[k+1] = matA[i][k]; 

      for (k = 0; k < r2; k++) 
      data[k+c1+1] = matB[k][j]; 

      pthread_create(&threads[count++], NULL,  
        mult, (void*)(data)); 
    } 

  key_t key = 1234;
  int *value;

  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  value = shmat(shmid, NULL, 0);

  printf("Result Matrix:\n"); 
  for (i = 0; i < max; i++)  
  { 
    void *k; 

    pthread_join(threads[i], &k); 
    
    int *p = (int *)k;
    value[i] = *p;
    printf("%-3d ", value[i]); 
    if ((i + 1) % c2 == 0) 
      printf("\n"); 
  }
  shmdt((void *) value);

  return 0; 
} 
```

- 4b adalah menampilan penjumlahan faktorial dari hasil perkalian matriks dari program 4a.c
```c
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void *find_fact(void* arg) 
{ 
  int data = *(int*)arg;
  unsigned long long k = 1; 

  for (int i = 1; i <= data; i++)
    k = k + i;

  unsigned long long *p = (unsigned long long*)malloc(sizeof(unsigned long long)); 
  *p = k; 

  pthread_exit(p); 
}

int main()
{
  key_t key = 1234;
  int *value;
  int fact[20];

  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  value = shmat(shmid, NULL, 0);

  for (int i = 0; i < 20; i++)  
  { 
    printf("%-3d ", value[i]); 
    if ((i + 1) % 5 == 0) 
      printf("\n"); 
  }
  
  pthread_t threads[20]; 
  for (int i = 0; i < 20; i++)  
  {
    // int *new_val = &i;
    int *new_val = &value[i];
    pthread_create(&threads[i], NULL, find_fact, (void *)new_val);
  }
  
  for (int i = 0; i < 20; i++)  
  { 
    void *k; 

    pthread_join(threads[i], &k);
    
    unsigned long long *p = (unsigned long long *)k;
    printf("%-4llu ",*p);
    if ((i + 1) % 5 == 0)
      printf("\n"); 
  }

  shmdt(value);
  shmctl(shmid, IPC_RMID, NULL);
}

```

- 4c adalah menampilkan jumlah file yang terdapat di direktori
```c
#include <stdlib.h>
#include <unistd.h>

int pipe1[2];

int main()
{
  if (pipe(pipe1) == -1)
    exit(1);

  if ((fork()) == 0) 
  {
    dup2(pipe1[1], 1);

    close(pipe1[0]);
    close(pipe1[1]);
    
    char *argv1[] = {"ls", NULL};
		execv("/bin/ls", argv1);
  }
  else
  {
    dup2(pipe1[0], 0);

    close(pipe1[0]);
    close(pipe1[1]);

    char *argv1[] = {"wc", "-l", NULL};
		execv("/usr/bin/wc", argv1);
  }
}

```