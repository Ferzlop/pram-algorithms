#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

#ifdef __INTELLISENSE__
#pragma diag_suppress 1696
#endif

void MergeSort(std::vector<int> &a);
std::vector<int> OddEvenMerge(const std::vector<int> &left, const std::vector<int> &right);
void Interchange(int &x, int &y);

int main()
{
  std::vector<int> a = {9, 7, 5, 3, 15, 2, 4, 6, 8, 10};
  MergeSort(a);
  std::cout << "Arreglo ordenado:" << std::endl;
  for (const auto &item : a)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}

void MergeSort(std::vector<int> &a)
{
  int n = a.size();
  if (n >= 2)
  {
    int mid = n / 2;
    std::vector<int> left(a.begin(), a.begin() + mid);
    std::vector<int> right(a.begin() + mid, a.end());

#pragma omp parallel sections
    {
#pragma omp section
      {
        MergeSort(left);
      }
#pragma omp section
      {
        MergeSort(right);
      }
    }

    std::vector<int> merged = OddEvenMerge(left, right);
    std::copy(merged.begin(), merged.end(), a.begin());
  }
}

std::vector<int> OddEvenMerge(const std::vector<int> &left, const std::vector<int> &right)
{
  int n = left.size() + right.size();
  std::vector<int> result(n);

  int i = 0, j = 0, k = 0;
#pragma omp while
  while (i < left.size() && j < right.size())
  {
    if (left[i] <= right[j])
    {
      result[k++] = left[i++];
    }
    else
    {
      result[k++] = right[j++];
    }
  }
#pragma omp while
  while (i < left.size())
  {
    result[k++] = left[i++];
  }
#pragma omp while
  while (j < right.size())
  {
    result[k++] = right[j++];
  }

#pragma omp parallel for
  for (int m = 1; m < n - 1; m += 2)
  {
    if (result[m] > result[m + 1])
    {
      Interchange(result[m], result[m + 1]);
    }
  }

  return result;
}

void Interchange(int &x, int &y)
{
  int temp = x;
  x = y;
  y = temp;
}
