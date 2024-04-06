#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string.h>

#ifdef __INTELLISENSE__
#pragma diag_suppress 1696
#endif

enum
{
  SIZE = 4
};

void sort(int a[])
{
  int win[SIZE];

#pragma omp parallel for
  for (int i = 0; i < SIZE; i++)
  {
    win[i] = 0;
  }

#pragma omp parallel for collapse(2)
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = i + 1; j < SIZE; j++)
    {
#pragma omp critical
      if (a[i] > a[j])
      {
        win[i] += 1;
      }
      else
      {
        win[j] += 1;
      }
    }
  }

  int a_copy[SIZE];
  memcpy(a_copy, a, SIZE * sizeof(int));
  // Using memcopy could bring errors so
  // it's possible to use a for loop to copy the array
  // however here we're trying to improve execution time
  //
  // for (int j = 0; j < SIZE; j++)
  // {
  //   a_copy[j] = a[j];
  // }

#pragma omp parallel for
  for (int i = 0; i < SIZE; i++)
  {
    a[win[i]] = a_copy[i];
  }
}

int main()
{
  int searchIn[SIZE] = {95, 10, 6, 15};

  sort(searchIn);

  printf("Sorted array:\n");
  for (int i = 0; i < SIZE; i++)
  {
    printf("%d", searchIn[i]);
    printf(" ");
  }

  printf("\n");

  return 0;
}