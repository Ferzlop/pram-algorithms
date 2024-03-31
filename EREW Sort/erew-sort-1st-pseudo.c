#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string.h>

#ifdef __INTELLISENSE__
#pragma diag_suppress 1696
#endif

enum
{
  SIZE = 16
};

void interchange(int a[], int p0, int p1)
{
  int copy = a[p1];
  a[p1] = a[p0];
  a[p0] = copy;
}

void divideHalf(int a[], int low[], int high[], int size)
{
  int half = size / 2;
#pragma omp parallel for
  for (int i = 0; i < half; i++)
  {
    low[i] = a[i];
  }

#pragma omp parallel for
  for (int i = half; i < size; i++)
  {
    high[i - half] = a[i];
  }
}

void oddEvenSplit(int a[], int odd[], int even[], int size)
{
#pragma parallel for
  for (int i = 0; i < size; i++)
  {
    if (i % 2 == 0)
    {
      even[i / 2] = a[i];
    }
    else
    {
      odd[i / 2] = a[i];
    }
  }
}

void oddEvenMerge(int a[], int size)
{
  if (size == 2)
  {

    if (a[0] > a[1])
    {
      interchange(a, 0, 1);
    }
  }
  else
  {
    int half = size / 2;
    int odd[half];
    int even[half];
    oddEvenSplit(a, odd, even, size);

#pragma omp parallel sections
    {
#pragma omp section
      {
        oddEvenMerge(odd, half);
      }
#pragma omp section
      {
        oddEvenMerge(even, half);
      }
    }

#pragma omp parallel for
    for (int i = 0; i < half; i++)
    {
#pragma omp critical
      {
        a[2 * i] = even[i];
        a[2 * i + 1] = odd[i];
      }
    }

#pragma omp parallel for
    for (int i = 0; i < half; i++)
    {
      if (a[2 * i + 1] > a[2 * i])
      {
        interchange(a, 2 * i + 1, 2 * i);
      }
    }
  }
}

void mergeSort(int a[], int size)
{
  if (size >= 2)
  {
    int half = size / 2;
    int aLow[half];
    int aHigh[half];

    divideHalf(a, aLow, aHigh, size);

#pragma omp parallel sections
    {
#pragma omp section
      {
        mergeSort(aLow, half);
      }
#pragma omp section
      {
        mergeSort(aHigh, half);
      }
    }
    oddEvenMerge(a, size);
  }
}

int main()
{
  if (SIZE % 2 != 0)
  {
    return 1;
  }

  int sorting[SIZE] = {15, 18, 16, 22, 23, 40, 35, 55, 53, 66, 60, 69, 70, 78, 72, 85};

  mergeSort(sorting, SIZE);

  printf("Sorted array:\n");
  for (int i = 0; i < SIZE; i++)
  {
    printf("%d", sorting[i]);
    printf(" ");
  }
  printf("\n");

  return 0;
}