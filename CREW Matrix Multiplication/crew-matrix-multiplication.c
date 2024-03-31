#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string.h>

#ifdef __INTELLISENSE__
#pragma diag_suppress 1696
#endif

enum
{
  SIZE = 2
};

int main()
{
  int a[SIZE][SIZE] = {{1, 2}, {3, 4}};
  int b[SIZE][SIZE] = {{5, 6}, {7, 8}};
  int c[SIZE][SIZE][SIZE] = {0};

#pragma omp parallel for collapse(3)
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      for (int k = 0; k < SIZE; k++)
      {
        c[i][j][k] = a[i][k] * b[k][j];
      }
    }
  }

#pragma omp parallel for collapse(3)
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      for (int k = 1; k < SIZE; k++)
      {
        c[i][j][0] += c[i][j][k];
      }
    }
  }

  printf("Product:\n");
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      printf("%d ", c[i][j][0]);
      printf(" ");
    }
    printf("\n");
  }

  return 0;
}