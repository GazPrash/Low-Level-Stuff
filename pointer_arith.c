#include<stdio.h>
#include<stdlib.h>

struct Person
{
  // size of struct Person : 68 bytes (64 * 4 + 32 bits)
  char name[64];
  int age;
};


int main(){
  struct Person People[100];
  struct Person* p_Person = &People[0];

  for (int i =0; i < 100; i++){
    p_Person->age = 0;
    p_Person++;
  }

  return 0;
}