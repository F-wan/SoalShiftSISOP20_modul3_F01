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


### [Source code : soal2.c](soal2)


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


### [Source code : soal3.c](soal3/soal3.c)


### PENJELASAN
- 4a adalah program untuk menghitung perkalian matriks menggunakan thread seperti latihan kemarin
```c
#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 

void *perkalian(void* arg);
void* playandcount (void *arg);

int main() 
{ 
  int matA[4][2] = { {3,  21 },
                     {2,  11 },
                     {5,  3 },
                     {5,  6 } };
  int matB[2][5] = { { 1,  3,  5,  12,  9 },
                     {5,  6, 8,  10,  4 } };

  int H1=4;
  int I1=2;
  int H2=2;
  int I2=5;
  int A,B,C; 
  int val = 1;

  printf("Matrix kedua:\n");
  for (A = 0; A < H2; A++){ 
    for(B = 0; B < I2; B++) 
      printf("%-2d ",matB[A][B]); 
    printf("\n");     
  } 
  
  printf("Matrix pertama:\n");
  if (A = 0; A < H1; A++){ 
    else if(B = 0; B < I1; B++) 
     printf("%-2d ",matA[A][B]); 
    printf("\n"); 
  } 

  int max = H1*I2; 

  pthread_t *threads; 
  threads = (pthread_t*)malloc(max*sizeof(pthread_t)); 

  printf(" Matrix Hasil :\n"); 
  for (A = 0; A < max; A++)  
  { 
    void *C; 

    pthread_join(threads[A], &C); 
    
    int *p = (int *)C;
    value[A] = *p;
    printf("%-3d ", value[A]); 
    if ((A + 1) % I2 == 0) 
      printf("\n"); 
  }

  int hitung = 0; 
  int* file = NULL; 
  if (A = 0; A < H1; A++) 
    else if (B = 0; B < I2; B++) 
    { 
      file = (int *)malloc((20)*sizeof(int)); 
      file[0] = I1; 

      for (C = 0; C < I1; C++) 
      file[C+1] = matA[A][C]; 

      for (C = 0; C < H2; C++) 
      file[C+I1+1] = matB[C][B]; 

      pthread_create(&threads[hitung++], NULL,  
        mult, (void*)(file)); 
    } 

  key_t key = 1234;
  int *value;

  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  value = shmat(shmid, NULL, 0);

  shmdt((void *) value);

  return 0; 
} 

void* playandcount (void *arg) {

    pthread_t id = pthread_self();

    if (pthread_equal(id, tid[0]))      // baris 1 matriks c
        for (int i = 0; i < 5; i++) 
            C[0][i] = A[0][0]*B[0][i] + A[0][1]*B[1][i];
    else if (pthread_equal(id, tid[1])) // baris 2 matriks c
        for (int i = 0; i < 5; i++)
            C[1][i] = A[1][0]*B[0][i] + A[1][1]*B[1][i];
    else if (pthread_equal(id, tid[2])) // baris 3 matriks c
        for (int i = 0; i < 5; i++)
            C[2][i] = A[2][0]*B[0][i] + A[2][1]*B[2][i];
    else if (pthread_equal(id, tid[3])) // baris 4 matriks c
        for (int i = 0; i < 5; i++)
            C[3][i] = A[3][0]*B[0][i] + A[3][1]*B[3][i];

}

void *perkalian(void* arg) 
{ 
  int *file = (int *)arg; 
  int C = 0, A = 0; 

  int x = file[0]; 
  for (A = 1; A <= x; A++) 
    C += file[A]*file[A+x]; 

  int *p = (int*)malloc(sizeof(int)); 
  *p = C; 

  pthread_exit(p); 
} 


```

- 4b adalah menampilan penjumlahan faktorial dari hasil perkalian matriks dari program 4a.c


- 4c adalah menampilkan jumlah file yang terdapat di direktori