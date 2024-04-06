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
  int a[SIZE][SIZE] = {
      {1, 2},
      {1, 2},
  };
  int b[SIZE][SIZE] = {
      {1, 2},
      {1, 2},
  };
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

  for (int l = 1; l <= (int)log2(SIZE); l++)
  {
#pragma omp parallel for collapse(3)
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        for (int k = 1; k <= SIZE / 2; k++)
        {
          if ((2 * k) % (2 * l) == 0)
          {
            c[i][j][(2 * k) - 1] += c[i][j][(2 * k) - 1 - (int)pow(2, l - 1)];
          }
        }
      }
    }
  }

  printf("Product:\n");
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      printf("%d ", c[i][j][SIZE - 1]);
      printf(" ");
    }
    printf("\n");
  }

  return 0;
}