#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdint.h>


void fetch_prng(const char * filename, int dsize){
  int * tarray = (int*)malloc(sizeof(intmax_t) * dsize);
  int * prng_array = (int*)malloc(sizeof(intmax_t) * dsize);

  FILE* datafile = fopen(filename, "a");

  char* stream = "";
  for (int i = 0; i < dsize; i++){
    time_t ctime = time(0);
    tarray[i] = (intmax_t) ctime;
    prng_array[i] = rand();

    stream = i == 0 ? "\n%d,%d\n" : "%d,%d\n";
    fprintf(datafile, stream, tarray[i], prng_array[i]);
  }

  fclose(datafile);
  free(tarray);
  free(prng_array);
}

int main(){
  srand(23);
  char * filename = "data/prng_data.csv";
  fetch_prng(filename, 2500);

}