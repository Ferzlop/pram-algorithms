# EREW Sort
```
function mergeSort(a[n]) recursive
  if n >= 2 then
    parallel call mergeSort(a[1:n/2] && a[n/2+1:n])
    call oddEvenMerge(a(n))

function oddEvenMerge(a[n])
  if n == 2 then
    if a[0] > a[1] then
      call interchange(a[0],a[1])
  else
    call oddEvenSplit(a[n], odd[n/2], even[n/2])
    parallel call oddEvenMerge(odd[n/2] && even[n/2])
    for 0 <= i < n/2 do in parallel
      a[2i] = odd[i]
      a[2i+1] = even[i]
    for 0 <= i <= n/2 do in parallel
      if a[2i + 1] > a[2i] then
        call interchange(a[2i+1], a[2i])
```

---

```
function oddEvenMergeSort(a[n], start, end) recursive
  if start < end
    middle = (start + end) / 2
    do in parallel 
      call oddEvenMergeSort(a[n], start, middle)
      call oddEvenMergeSort(a[n], middle + 1, end)
    parallelOddEvenMerge(a[n], start, end)

function parallelOddEvenMerge(a[n], start, end) recursive
  if end - start > 1
    middle = (start + end) / 2
    do in parallel
      parallelOddEvenMerge(a[n], start, middle)
      parallelOddEvenMerge(a[n], middle + 1, end)
    do in parallel
      parallelOddEvenMerge(a[n], start + 1, end)
      parallelMerge(a[n], start, end)

function parallelMerge(a[n], start, end)
  middle = (start + end) / 2
   for start <= i <= middle do in parallel
    if a[i] > a[middle + 1]
      temp = a[i]
      a[i] = a[middle + 1]
      a[middle + 1] = temp
    for start + 1 <= i <= end - 1 (step by 2) do in parallel
      if (a[i] > a[i+1])
        temp = a[i]
        a[i] = a[i+1]
        a[i+1] = temp
```