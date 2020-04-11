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
