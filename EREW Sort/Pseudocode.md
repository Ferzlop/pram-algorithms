# EREW Sort
```
function mergeSort(a[n]) recursive
  if n >= 2 then
    parallel call mergeSort(a[1:n/2] | a[n/2+1:n])
    call oddEvenMerge(a(n))

function oddEvenMerge(a[n])
  if n == 2 then
    if a[0] > a[1] then
      call interchange(a[0],a[1])
  else
    call oddEvenSplit(a[n], odd[n/2], even[n/2])
    parallel call oddEvenMerge(odd[n/2] | even[n/2])
    for 0 <= i < n/2 do in parallel
      a[2i] = odd[i]
      a[2i+1] = even[i]
    for 0 <= i <= n/2 do in parallel
      if a[2i + 1] > a[2i] then
        call interchange(a[2i+1], a[2i])
```