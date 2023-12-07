#include<stdio.h>
#include<stdlib.h>


typedef struct{
  int value;
  int refCount;

} SafeInt;

SafeInt* SafeMalloc(int size){
  return (SafeInt *)malloc(sizeof(SafeInt) * size);
}

int CalcSum(SafeInt * array, int length){
  int sum_value = 0;
  for (int i = 0; i < length; i++){
    sum_value += array[i].value;
  }
  return sum_value;
}

void OtherFunction(){
  puts("Start of some other function that does some other stuff, out of scope of SafeInt.\n");
  int i = 0;
  while (i <= 1000)
  {
    i *= 1.1;
  }
  puts("End of some other function that does some other stuff, out of scope of SafeInt.\n");
}

void OtherFunction2(){
  puts("Start of some other function2 that does some other stuff, out of scope of SafeInt.\n");
  int i = 0;
  while (i <= 1000)
  {
    i *= 2.2;
  }
  puts("End of some other function2 that does some other stuff, out of scope of SafeInt.\n");
}

int main(){
  // Initialize Your Integer Array
  SafeInt* Sint = SafeMalloc(4);
  Sint[0].value = 2;
  Sint[1].value = 4;
  Sint[2].value = 12;
  Sint[3].value = 4;
  printf("%d", CalcSum(Sint, 4));
  
  OtherFunction();
  // ---> Sint should'nt exist in memory by this point as 
  //      no function or var is referencing it (gone out of scope)
  OtherFunction2();
  // end of script
}