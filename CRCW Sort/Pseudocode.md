# CRCW Sort
```
function crcwSort(a[n])
  for 0 <= i < n do in parallel
    win[i] = 0

  for 0 <= i < n do in parallel
    for i+1 <= j < n
      if a[i] > a[j] then
        win[i] += 1
      else
        win[j] += 1

  for 0 <= i < n do in parallel
    a[win[i]] = a[i]
```