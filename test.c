#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>


typedef struct {
  float* array;
  int rows;
  int columns;
} MyStruct;

void assignArrayToStruct(MyStruct* structPtr, float array[2][3]) {
  structPtr->array = (float*)array;
  structPtr->rows = 2;
  structPtr->columns = 3;
}

int main() {
  // float array[2][3] = {{1, 2, 3}, {4, 5, 6}};

  // MyStruct struct1;
  // assignArrayToStruct(&struct1, array);

  // // Print the values of the array.
  // for (int i = 0; i < struct1.rows; i++) {
  //   for (int j = 0; j < struct1.columns; j++) {
  //     printf("%f ", struct1.array[i * 3 + j]);
  //   }
  //   printf("\n");
  // }
  char c1 = 'a';
  char c2 = 'c';
  printf("%d", c1 > c2);

  return 0;
}
