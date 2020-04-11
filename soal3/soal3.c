#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

char buf[PATH_MAX+1];
char path[PATH_MAX+1], *p;
char *nama_file;
char *alamat_file;
char destpath[1024];
void *cek_file(void *arg);
int index_file = 0;
pthread_mutex_t lock;
pthread_t tid;

// fungsi buat mencari path dari file c
void path_c(char *str)
{
  FILE *fp;
  char buf[4096], *p;

  *str = '\0';
  if(!(fp = fopen("/proc/self/maps", "r"))) return;

  fgets(buf, sizeof(buf), fp);
  fclose(fp);

  *(p = strchr(buf, '\n')) = '\0';
  
  while(*p != ' ') p--;

  strcpy(str, p+1);
  str[PATH_MAX] = '\0';
}

// list semua file yang ada di direktori file c dan dimasukkan di file "list_file.txt"
void list_file(char *path)
{
  FILE *f = fopen("list_file.txt", "w");
  if (f == NULL)
  {
    puts("Error dalam membuka file");
    exit(1);
  }

  DIR *d;
  struct dirent *dir;

  d = opendir(path);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      if (dir->d_type == DT_REG)
      {
        fprintf(f, "%s%s\n", path, dir->d_name);
        index_file++;
      }
    }
    closedir(d);
    fclose(f);
  }
}

// fungsi:
// 1. Read per line di list_file.txt 
// 2. Buat thread dan run thread ke cek_file
void read_path(char *arg)
{
  FILE* filePointer;
  int bufferLength = 255;
  char buffer[bufferLength];

  // Variabel temp buat nyimpan argumen
  char *temp;
  temp = strrchr(arg, '/') + 1;
  strcat(temp, "\n");

  filePointer = fopen("list_file.txt", "r");

  printf("JUMLAH FILES: %d\n", index_file);

  // Error handling mutex
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
    puts("Gagal buat mutex");
    exit(EXIT_FAILURE);
  }

  // Buat thread
  while(fgets(buffer, bufferLength, filePointer))
  {
    nama_file = strrchr(buffer, '/') + 1;

    // Skip file txt dan file program
    if (strcmp(nama_file, "list_file.txt\n") == 0 || strcmp(nama_file, temp) == 0)
    {
      printf("%s skipped\n", nama_file);
      continue;
    }
    else{ 
      // WAKTU NYA MEMBUAT THREAD :)
      buffer[strcspn(buffer, "\r\n")] = 0;  // buat hapus enter di buffer

      pthread_create(&(tid), NULL, cek_file, (void *)buffer);

      pthread_join(tid, NULL);
    }
  }
  fclose(filePointer);

  // Hapus file "list_file.txt"
  if (remove("list_file.txt") == 0) puts("list_file.txt sukses dihapus");
  else
    puts("list_file.txt tidak bisa dihapus");
}

// fungsi cari ekstensi file
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

// fungsi cek dan buat folder
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

  struct stat st = {0};

  if (stat(foldername, &st) == -1)
  {
    printf("mkdir %s\n", foldername);
    mkdir(foldername, 0700);
  } 
    
}

// fungsi buat move file
void* move_file(char *pathc, char *ekstensi, char *nama_file, char *alamat_asal)
{
  // char destpath[1024];
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

void *cek_file(void *arg)
{
  // Lock mutex
  pthread_mutex_lock(&lock);

  // 1. Ambil nama file
  nama_file = strrchr((char *)arg, '/') + 1;
  alamat_file = (char *)arg;

  printf("Nama file: %s\n", nama_file);
  printf("Alamat file: %s\n", alamat_file);

  // 2. Cari ada ekstensi nya atau gak?
  if(cari_ekstensi(nama_file))
  { 
    cek_folder(cari_ekstensi(nama_file)); // Cek kalau gaada folder ekstensi
    move_file(path, cari_ekstensi(nama_file), nama_file, alamat_file); // Move file ke folder ekstensi
  }
  else
  { 
    cek_folder("Unknown"); // Cek kalau gaada folder "Unknown"
    move_file(path, "Unknown", nama_file, alamat_file); // Move file ke folder "Unknown"
  }

  // Unlock mutex
  pthread_mutex_unlock(&lock);
  return NULL;
}

int main(int argc, char **argv)
{
  path_c(buf);

  strcpy(path, buf);
  if((p = strrchr(path, '/')))
    *(p+1) = '\0';
  
  // printf("Path file c: %s\n", path);

  int i = 2;
  // pthread_t tid[argc - 1];

  // Error handling jika tidak ada argumen yang di input
  if (argc == 0)
  {
    puts("Mohon masukkan argumen pada program (-f, *, atau -d)");
    exit(EXIT_FAILURE);
  }
  
  // Error handling mutex
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
    puts("Gagal buat mutex");
    return 1;
  }
  
  // Testcase tiap argument
  if(strcmp(argv[1], "-f") == 0)
  {
    puts("Masuk ke -f");
    
    // buat thread
    while (i < argc)
    {
      pthread_create(&(tid), NULL, cek_file, (void *)argv[i]);
      pthread_join(tid, NULL);
      i++;
    }
  }
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
    list_file(path);

    // Read path tiap line kecuali list_file.txt dan nama program
    read_path(argv[0]);
  }
  else if(strcmp(argv[1], "-d") == 0)
  {
    puts("Masuk ke -d");

    // Error handling ketika path directory yang dimasukkan lebih dari 1
    if (argc > 3)
    {
      puts("Mohon hanya memasukkan satu path directory!");
      exit(EXIT_FAILURE);
    }
    
    // List semua path dari file untuk kemudian diproses oleh thread
    list_file(argv[2]);

    // Read path tiap line kecuali list_file.txt dan nama program
    read_path(argv[0]);
  }

  return 0;
}