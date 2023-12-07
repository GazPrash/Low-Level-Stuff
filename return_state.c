#include<stdio.h>
#include<stdlib.h>

int func_strlen(const char * str){
  int i = 0;
  while(str[i++])
    ;;
  return i;
}

int main(){
  const char* str_arr = "This is bombastic!";
  printf("%d", func_strlen(str_arr));
  return 0;
}