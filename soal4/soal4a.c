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
