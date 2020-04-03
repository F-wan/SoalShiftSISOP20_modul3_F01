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

