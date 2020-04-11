# SoalShiftSISOP20_modul3_F01

## directory soal
- [Soal 2](soal2/)
- [Soal 3](soal3/)
- [Soal 4](soal4/)

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
- Pada soal no 3 kita diminta untuk mengkategorikan fila pada lokasi tertentu berdasarkan argumen yang diberikan
- Apabila argumennya `"-f"`, program akan mengkategorikan file yang ada pada argumen ke dalam folder berdasarkan ekstensi file tersebut, dan folder berada pada working directory program
- Apabila argumen pertama adalah `"-f"`, maka program tidak akan menerima input berupa folder
```c
if(strcmp(argv[1], "-f") == 0)
{
  puts("Masuk ke -f");
  
  while (i < argc)
  {
    if(!is_regular_file(argv[i]))
    {
      puts("EXIT not a file");
      exit(EXIT_FAILURE);
    }

    pthread_create(&(tid), NULL, cek_file, (void *)argv[i]);
    pthread_join(tid, NULL);
    i++;
  }
}
```
- Apabila argumennya `"*"`, program akan mengkategorikan semua file yang ada pada working directory ke dalam folder berdasarkan ekstensinya
```c
else if(strcmp(argv[1], "*") == 0)
{
  puts("Masuk ke *");

  // Error handling ketika argumennya lebih
  if (argc > 2)
  {
    puts("Mohon tidak memasukkan argumen lain ketika menggunakan mode *");
    exit(EXIT_FAILURE);
  }
  
  // List semua path file pada working directory
  printf("path = ");
  puts(path);
  list_file(path);

  // Read path tiap line kecuali list_file.txt dan nama program
  read_path(argv[0]);
}
```
- Apabila argumen yang diterima adalah`"-d"`, maka program akan mengkategorikan semua file pada folder yang diberikan pada argumen ke dalam folder berdasarkan ekstensi file tersebut, dan folder berada pada working directory program
```c
else if(strcmp(argv[1], "-d") == 0)
{
  puts("Masuk ke -d");

  if (argc > 3)
  {
    puts("Mohon hanya memasukkan satu path directory!");
    exit(EXIT_FAILURE);
  }
  
  list_file(argv[2]);
  read_path(argv[0]);
}
```

- Kemudian pada fungsi `cek_file`, kita memeriksa apakah file memiliki ekstensi seperti `.zip`, `.jpg`, `.JPG`, dan lain sebagainya.
- Apabila tidak memiliki ekstensi, file akan masuk ke folder `Unknown`
```c
void *cek_file(void *arg)
{
  // Lock mutex
  pthread_mutex_lock(&lock);

  nama_file = strrchr((char *)arg, '/') + 1;
  alamat_file = (char *)arg;

  printf("Nama file: %s\n", nama_file);
  printf("Alamat file: %s\n", alamat_file);

  if(cari_ekstensi(nama_file))
  { 
    cek_folder(cari_ekstensi(nama_file));
    move_file(path, cari_ekstensi(nama_file), nama_file, alamat_file);
  }
  else
  { 
    cek_folder("Unknown");
    move_file(path, "Unknown", nama_file, alamat_file);
  }

  // Unlock mutex
  pthread_mutex_unlock(&lock);
  return NULL;
}
```

- Pada fungsi `cari_ekstensi`, program akan memeriksa ekstensi dari file dan mengembalikan ekstensi file tersebut.
- Kemudian karena pada soal file `.jpg` dan `.JPG` dimasukkan ke dalam 1 folder, maka kami anggap mereka masuk ke folder `jpg`.
- Maka dari itu dilakukan perubahan ekstensi file menjadi lower case dengan fungsi `tolower`
```c
char *cari_ekstensi(char *filename)
{
  char *temp = filename;

  char *extension = strrchr(temp, '.');
  printf("dot = %s\n", extension);


  if(!extension || extension == temp) return 0;
  
  int len = 0;
  char tipe[100];

  extension = extension+1;
  strcpy(tipe, extension);

  printf("extension awal = %s\t\t", extension);
  printf("tipe awal = %s\n", tipe);

  if((extension[strlen(extension)-1] >= 'a' && extension[strlen(extension)-1] <= 'z') || (extension[strlen(extension)-1] >= 'A' && extension[strlen(extension)-1] <= 'Z'))
  {
    for(int i = 0; tipe[i]; i++)
    {
      tipe[i] = tolower(tipe[i]);
      len++;
    }
  }

  extension = tipe;
  printf("len = %d\t\t\t\t extension = ", len);
  puts(extension);

  return extension;
}
```

- Setelah kita mengetahui nama folder tempat file akan dipindahkan, kita cek terlebih dahulu apakah folder tersebut ada.
- Jika tidak ada, maka kita buat folder tersebut
- Semua proses ini dilakukan pada fungsi `cek_folder`
```c
void* cek_folder(char *foldername)
{
  int len = 0;
  char tipe[100];

  strcpy(tipe, foldername);

  printf("foldername awal = %s\t\t", foldername);
  printf("tipe awal = %s\n", tipe);

  if(!strcmp(foldername, "Unknown"))
  {

  }
  else if((foldername[strlen(foldername)-1] >= 'a' && foldername[strlen(foldername)-1] <= 'z') || (foldername[strlen(foldername)-1] >= 'A' && foldername[strlen(foldername)-1] <= 'Z'))
  {
    for(int i = 0; tipe[i]; i++)
    {
      tipe[i] = tolower(tipe[i]);
      len++;
    }
  }

  foldername = tipe;
  printf("len = %d\t\t\t\t foldername = ", len);
  puts(foldername);
  int exist = 0;

  DIR *d;
  struct dirent *dir;
  d = opendir(".");

  while((dir = readdir(d)) != NULL) //smpe gada file lagi di dir
  {
    if(strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name, "..") == 0) continue;

    //bukan file = dir
    if(!is_regular_file(dir->d_name))
    {
      if(!strcmp(foldername, dir->d_name))
      {
        printf("dir %s exist\n", dir->d_name);
        exist = 1;
      }
    }
  }
  closedir(d);

  if (!exist)
  {
    printf("mkdir %s\n", foldername);
    mkdir(foldername, 0700);
  }
  else
  {
    puts("directory exist");
  }
}
```

- Setelah memastikan bahwa folder ada dan siap untuk memindahkan file ke sana, kita pindahkan file ke folder yang diinginkan menggunakan fungsi `move_file`
- fungsi ini akan mengubah path ke file menjadi path baru berdasarkan lokasi folder tempat file akan dipindahkan
```c
void* move_file(char *pathc, char *ekstensi, char *nama_file, char *alamat_asal)
{
  sprintf(destpath, "%s%s/%s", pathc, ekstensi, nama_file);

  printf("Asal: %s\nDestinasi: %s\n\n", alamat_asal, destpath);

  if (rename (alamat_asal, destpath))
  {
    // something went wrong
    if (errno == EXDEV) {
        // copy data and meta data 
    } else { perror("rename"); exit(EXIT_FAILURE); };
  } 
  else { // the rename succeeded
  }
}
```

### SCREENSHOT HASIL
- uji coba argumen `"-f"`
- dapat dilihat bahwa file `test.c` masuk ke folder `c`

![f.png](/screenshot/f.png)

- Dan apabila argumen yang diberikan adalah folder, maka program akan berhenti

![fwan.png](/screenshot/fwan.png)

- uji coba argumen `"*"`
- dapat dilihat bahwa semua file `.c` masuk ke folder `c`

![*.png](/screenshot/*.png)



- uji coba argumen `"-d"`
- folder yang dijadikan input dengan argumen `"-d"`

![d1.png](/screenshot/d1.png)

- Jalankan program dengan arguman `"-d"`

![d2.png](/screenshot/d2.png)

- Program selesai dijalankan

![d3.png](/screenshot/d3.png)

- Hasilnya, semua file akan dikelompokkan pada folder berdasarkan ekstensinya dan folder berada di working directory

![d4.png](/screenshot/d4.png)

- Contoh isi folder `jpg`

![d5.png](/screenshot/d5.png)



## Soal no. 4
### PENJELASAN 4A
### [Source code : soal4a.c](soal4/soal4a.c)
- Di soal 4a ini kita membuat program yang dapat meng-kalikan matrik 5x2 dengan matriks 2x5. yang berisikan angka 1-20. Isi dari matriks di definisikan di dalam kodingan. Hasil akan di tampilkan dan juga di simpan agar bisa di gunakan di program 4b.
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/ipc.h>


int (*value)[10];
int hasil = 0;
int matA[10][10], matB[10][10], 
                        RowOf_A =4 , ColumnOf_A=2, RowOf_B=2, ColumnOf_B=5; 
pthread_t thread1, thread2, final; 

//matriks pertama
void *A(void *arg) { 
   matA[0][0]=2; 
   matA[0][1]=1; 
   matA[1][0]=4; 
   matA[1][1]=3; 
   matA[2][0]=2; 
   matA[2][1]=1; 
   matA[3][0]=4; 
   matA[3][1]=3;
   return NULL;
}

void *B(void *arg){
   matB[0][0]=4;
   matB[0][1]=1; 
   matB[0][2]=2;
   matB[0][3]=3; 
   matB[0][4]=1; 
   matB[1][0]=2;
   matB[1][1]=1; 
   matB[1][2]=3; 
   matB[1][3]=1; 
   matB[1][4]=3; 
   return NULL;
}

void *matrix_multiplication(void *arg){
   for(int i=0;i<RowOf_A;i++){
      for(int j=0;j<ColumnOf_B;j++){
         for(int k=0;k<ColumnOf_A;k++){
            hasil+=matA[i][k] * matB[k][j]; 
         }
         value[i][j]= hasil; 
         hasil = 0; 
      }
   }
   return NULL;
}

int main(){
   
   key_t key = 1234;
   int shmid = shmget(key, sizeof(int[10][10]), IPC_CREAT | 0666); 
   value = shmat(shmid, 0, 0);

   pthread_create(&thread1, NULL, A, NULL); 
   pthread_join(thread1,NULL);

   pthread_create(&thread2, NULL, B, NULL); 
   pthread_join(thread2,NULL);

   for(int i=0;i<RowOf_A;i++){
      for(int j=0;j<ColumnOf_B;j++){ 
         value[i][j]=0;
      }
      pthread_create(&final, NULL, matrix_multiplication, NULL); 
      pthread_join(final,NULL);
   }

  
   printf("A*B : \n");
   for(int i=0; i<RowOf_A; i++){ 
      for(int j=0;j<ColumnOf_B;j++){  
         printf("%d\t", value[i][j]); 
      }
      printf("\n");
   }
}

```
### SCREENSHOT HASIL
- uji coba soal 4a

![4a.png](/screenshot/4a.png)

### PENJELASAN 4B
### [Source code : soal4b.c](soal4/soal4b.c)

- Di soal 4b ini kita membuat program yang mengambil hasil perkalian matriks dari soal 4a dan menampilkan hasilnya ke layar. Setelah itu melakukan pencarian faktorial dari masing-masing angka pada matriks dan ditampilkan pada layar.
```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>


unsigned long long num; 
int row = 4, column = 5; 

unsigned long long factorial(unsigned long long a){  
    if(a==0 || a==1) return 1;
    else return a+ factorial(a-1); 
}

//fungsi faktorial
void *faktorial(void *arg){
    
    key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
    
    printf("Hasil faktorial pertambahan matriks ialah: \n");
    
    for(int i=0;i<row;i++){ 
        for(int j=0;j<column;j++){ 
            num=value[i][j]; 
            printf("%llu\t", factorial(num)); 
        }
        printf("\n");
    }
    pthread_exit(0); // keluar thread
}

void main(){
    pthread_t thread;
    
    key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid,NULL ,0 );

    printf("Hasil perkalian dari matriks A dan B adalah: \n");
    
    for(int i=0;i< 4;i++){
        for(int j=0;j<5;j++){
            printf("%d\t", value[i][j]);
        }
        printf("\n");
    }
    pthread_create(&thread, NULL, faktorial, NULL); 
    pthread_join(thread,NULL); 
}

```
### SCREENSHOT HASIL
- uji coba soal 4b

![4b.png](/screenshot/4b.png)

### PENJELASAN 4C
### [Source code : soal4c.c](soal4/soal4c.c)
- Di soal 4c kita mencari tahu ada berapa jumlah file yang terdapat di direktori. Setelah mengetahui jumlah file terus jumlah file di tampilkan ke layar.
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
### SCREENSHOT HASIL
- Uji coba soal 4c
- Hasil yang ditunjukkan adalah 6
- Hal ini terbukti saat menjalankan perintah `ls` pada terminal muncul 6 file pada working directory
![4c.png](/screenshot/4c.png)
