#include <stdio.h>
#include <omp.h>
#include <math.h>

#ifdef __INTELLISENSE__
#pragma diag_suppress 1696
#endif

enum
{
  SIZE = 8
};

int main()
{
  int a[SIZE] = {5, 2, 10, 1, 8, 12, 7, 3};

  printf("Original array:\n");

  for (int i = 0; i < SIZE; i++)
  {
    printf("%d", a[i]);
    printf(" ");
  }
  printf("\n");

  int i, j;

  for (i = 1; i <= (int)log2(SIZE); i++)
  {
    {
#pragma omp parallel for
      for (j = 1; j <= SIZE / 2; j++)
      {
        if (2 * j % (int)pow(2, i) == 0)
        {
          a[2 * j - 1] += a[(2 * j - 1) - (int)pow(2, i - 1)];
        }
      }
    }
    printf("Modified array:\n");

    for (int i = 0; i < SIZE; i++)
    {
      printf("%d", a[i]);
      printf(" ");
    }
    printf("\n");
  }

  return 0;
}