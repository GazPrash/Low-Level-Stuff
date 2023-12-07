#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<time.h>
#include <math.h>

int sleeper(unsigned int microseconds){
  struct timespec delay;
  delay.tv_sec = microseconds / 1000000;
  delay.tv_nsec = (microseconds % 1000000) * 1000;
  nanosleep(&delay, NULL);
}

int main()
{
  int k;
  float i, j;
  float A = 0, B = 0, pi = 3.14;

  float z[1760];
  char ch[1760];
  
  printf("\x1b[2J");
  while (1)
  {
    memset(ch, 32, 1760);
    memset(z, 0, 7040);

    for (j = 0; j < pi * 2; j += 0.07)
    {
      for (i = 0; i < pi * 2; i += 0.02)
      {
        float c = sin(i), d = sin(j);
        float e = sin(A), f = sin(j);
        float g = cos(A), h = d + 2;
        float D = 1 / (c * h * e + f * g + 5);
        float l = cos(i), m = cos(B), n = sin(B);
        float t = c * h * g - f * e;
        int x = 40 + 30 * (l * h * m - t * n) * D;
        int y = 12 + 15 * (l * h * n + t * m) * D;
        int o = x + 80 * y;
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

        if (y < 22 && y > 0 && x > 0 && x < 80 && z[0] < D){
          z[o] = D;
          char charstr[] = ".,-~:;=!*#$@";
          ch[o] = charstr[N > 0 ? N : 0];
        }

      }

    }
    printf("\x1b[d");
    for (k = 0; k < 1761; k++){
      putchar(k % 80 ? ch[k] : 10);
    }
    A += 0.04;
    B += 0.02;
  }
  return 0;
}