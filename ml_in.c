#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include<math.h>

// typedef struct {
//   float training_data[][2];

// } onep_model;

void printArray(float arrptr[][2], int row, int col)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      printf("%f |", arrptr[i][j]);
    }
    printf("\n");
  }
}                     

float *randn(int n, float multiplier)
{
  float *randarr = (float *)malloc(sizeof(float) * n);
  for (int i = 0; i < n; i++)
  {
    float rn = ((float)rand() / RAND_MAX) * multiplier;
    randarr[i] = rn;
  }

  return randarr;
}

// y = mx + c
float model_eq(float m, float x, float c)
{
  return m*x + c;
}

float predict()
{
  return 0.0;
}

double *evaluate_model(float training_data[][2], int datalen, float p)
{
  int * truthy = (int* ) malloc(sizeof(int) * datalen);
  double * squared_residuals = (double* ) malloc(sizeof(double) * datalen);
  
  for (int i = 0; i < datalen; i++){
    float x = training_data[i][0];
    float y = training_data[i][1];
    squared_residuals[i] = pow(y - p * x, 2);
    printf("actual-factual : %f, predicted : %f\n", y, x * p);
    truthy[i] = abs(x*p - y) < 1 ? 1 : 0;
  }
  return squared_residuals;
}

float cost_function(float x, float y, float weight, float bias){
  return pow((x*weight + bias) - y, 2);

}

void train_model(float training_data[][2], int datalen)
{


}

void optimizer(){

}


int main()
{
  srand(time(0));
  // task();
  // int n = 17;
  // float multi = 1;
  // float *arr = randn(n, multi);
  // for (int i = 0; i < n; i++)
  // {
  //   printf("%f, ", arr[i]);
  // }
  
  float data[][2] = {
    {0, 3},
    {1, 7},
    {2, 11},
    {3, 15},
    {4, 19},
    {5, 23},
    {6, 27},
    {7, 31},
  };
  int datalength = sizeof(data) / (sizeof(float) * 2);
  // printArray(data, datalength, 2);
  float weight = randn(1, 1)[0] * 10.0f;
  float bias = randn(1, 1)[0] * 5.0f;
  float lr = 1e-3, epsilon = 1e-3;
  int epochs = 6000;
  // double* res = evaluate_model(data, datalength, p);
  // double SSE = 0;
  // for (int i = 0; i < datalength; i++)
  // {
  //   printf("%f, ", res[i]);
  //   SSE += res[i];
  // }

  // printf("\nSSE : %f", SSE);
  for (int e = 0 ; e < epochs; e++){
    float cost = 0, cost_ep = 0;    
    for (int i = 0; i < datalength; i++){
      float x = data[i][0];
      float y = data[i][1];
      cost += cost_function(x, y, weight, bias);
      cost_ep += cost_function(x, y, weight + epsilon, bias);
      // printf("actual-factual : %f, predicted : %f\n", y, x * p);
      // printf("cost : %f\n", cost);
    }
    cost /= datalength;
    cost_ep /= datalength;
    float differential = (cost_ep - cost)/epsilon;
    weight -= differential * lr;
    bias -= differential * lr;
    if (e % 500 == 0){
      printf("Iteration (%d) and W : %f and B : %f and loss : %f\n", e, weight, bias, cost);
    }
  }
  printf("----------------------------------------\n");
  printf("Perfected Weight and Loss : %f and %f", weight, bias);    

  return 0;
}