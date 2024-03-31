#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#ifdef __INTELLISENSE__
#pragma diag_suppress 1696
#endif

void oddEvenMergeSort(int arr[], int start, int end);
void parallelOddEvenMerge(int arr[], int start, int end);
void parallelMerge(int arr[], int start, int end);

void oddEvenMergeSort(int arr[], int start, int end)
{
  if (start < end)
  {
    int middle = (start + end) / 2;
#pragma omp parallel sections
    {
#pragma omp section
      oddEvenMergeSort(arr, start, middle);
#pragma omp section
      oddEvenMergeSort(arr, middle + 1, end);
    }
    parallelOddEvenMerge(arr, start, end);
  }
}

void parallelOddEvenMerge(int arr[], int start, int end)
{
  if (end - start > 1)
  {
    int middle = (start + end) / 2;

#pragma omp parallel sections
    {
#pragma omp section
      parallelOddEvenMerge(arr, start, middle);
#pragma omp section
      parallelOddEvenMerge(arr, middle + 1, end);
    }

#pragma omp parallel sections
    {
#pragma omp section
      parallelOddEvenMerge(arr, start + 1, end);
#pragma omp section
      parallelMerge(arr, start, end);
    }
  }
}

void parallelMerge(int arr[], int start, int end)
{
  int middle = (start + end) / 2;

#pragma omp parallel for
  for (int i = start; i <= middle; i++)
  {
    if (arr[i] > arr[middle + 1])
    {
#pragma omp critical
      {
        int temp = arr[i];
        arr[i] = arr[middle + 1];
        arr[middle + 1] = temp;
      }
    }
  }

#pragma omp parallel for
  for (int i = start + 1; i <= end - 1; i += 2)
  {
    if (arr[i] > arr[i + 1])
    {
#pragma omp critical
      {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
      }
    }
  }
}

int main()
{
  int arr[] = {42, 15, 78, 3, 91, 27, 55, 68, 10, 84, 36, 50, 7, 20, 63, 95};
  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Array before sorting: \n");
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");

  oddEvenMergeSort(arr, 0, n - 1);

  printf("Array after sorting: \n");
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");

  return 0;
}
