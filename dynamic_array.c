#include<stdio.h>
#include<stdlib.h>

typedef struct IntegerArray{
  int* data_array;
  size_t array_sz;
  size_t capacity;
  size_t increase_capacity;

} IntegerArray;

void push_back(IntegerArray * arr_ptr, int element){
  if (arr_ptr->array_sz <= arr_ptr->capacity){
    size_t new_capacity = arr_ptr->capacity + arr_ptr->increase_capacity;
    arr_ptr->data_array = realloc(arr_ptr->data_array, new_capacity);
    arr_ptr->capacity = new_capacity;
  }
  arr_ptr->data_array[arr_ptr->array_sz] = element;
  arr_ptr->array_sz++;
}

int main(){
  IntegerArray arr = {0};
  arr.data_array = (int*)malloc(sizeof(int) * 10);
  arr.capacity = 10;
  arr.increase_capacity = 10;

  push_back(&arr, 0);
  push_back(&arr, 1);
  push_back(&arr, 2);

  for (int i =0; i < 3; i++){
    printf("%d-", arr.data_array[i]);
  }

  return 0;
}