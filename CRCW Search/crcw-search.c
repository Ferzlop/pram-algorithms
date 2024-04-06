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

int minima(int a[])
{

  int win[SIZE];
  int indexMin;

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
      if (a[i] > a[j])
      {
        win[i] = 1;
      }
      else
      {
        win[j] = 1;
      }
    }
  }

#pragma omp parallel for
  for (int i = 0; i < SIZE; i++)
  {
    if (win[i] == 0)
    {
      indexMin = i;
    }
  }

  return a[indexMin];
}

int main()
{
  int searchIn[SIZE] = {95, 10, 6, 15};

  printf("The lowest value is:\n");
  printf("%d", minima(searchIn));
  printf("\n");

  return 0;
}