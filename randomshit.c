#include<stdlib.h>
#include<stdio.h>


int main(){
  int holdlimit = 32;
  int * arr = (int*) malloc(sizeof(int) * holdlimit);
  for (int i = 0; i < holdlimit; i++){
    arr[i] = i*(i+1);
  }

  for (int k = 0; k < holdlimit; k++){
    printf("%d | ", arr[k]);
  }



  for (int k = 0; k < holdlimit; k++){
    free(arr);
    arr++;
  }

  printf("\n Freed Memory \n");
  
  for (int k = 0; k < holdlimit; k++){
    printf("%d | ", arr[k]);
  }

}