#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#ifdef __INTELLISENSE__
#pragma diag_suppress 1696
#endif

enum
{
  SIZE = 16
};

void broadcast(int a[], int x)
{
  a[0] = x;
  for (int i = 1; i <= (int)log2(SIZE); i++)
  {
#pragma omp parallel for
    for (int j = (int)pow(2, i - 1); j < (int)pow(2, i); j++)
    {
      a[j] = a[j - (int)pow(2, i - 1)];
    }
  }
}

int minima(int a[0])
{
  for (int i = 1; i <= (int)log2(SIZE); i++)
  {
#pragma omp parallel for
    for (int j = 0; j < SIZE / (2 * i); j++)
    {
#pragma omp critical
      if (a[2 * j] > a[2 * j + 1])
      {
        a[j] = a[2 * j + 1];
      }
      else
      {
        a[j] = a[2 * j];
      }
    }
  }
  return a[0];
}

int erewSearch(int l[], int x)
{
  int temp[SIZE];
  broadcast(temp, x);

#pragma omp parallel for
  for (int i = 0; i < SIZE; i++)
  {
    if (l[i] == temp[i])
    {
      temp[i] = i;
    }
    else
    {
      temp[i] = INT_MAX;
    }
  }

  return minima(temp);
}

int main()
{
  int searchIn[SIZE] = {2, -1, 23, -4, 2, 5, -2, 0, 5, 1, 5, -5, 8, 5, 3, -2};
  int searchFor = 5;

  int position = erewSearch(searchIn, searchFor);

  printf("The value was founded in position: ");
  printf("%d", position);
  printf("\n");

  return 0;
}