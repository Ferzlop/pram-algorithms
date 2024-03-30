#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string.h>

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

  for (int i = 1; i <= (int)log2(SIZE); i++)
  {
    {
      int a_copy[SIZE];
      memcpy(a_copy, a, sizeof(a));
      // Using memcopy could bring errors so
      // it's possible to use a for loop to copy the array
      // however here we're trying to improve execution time
      //
      // for (int j = 0; j < SIZE; j++)
      // {
      //   a_copy[j] = a[j];
      // }

#pragma omp parallel for
      for (int j = (int)pow(2, i - 1); j < SIZE; j++)
      {
        a[j] += a_copy[j - (int)pow(2, i - 1)];
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