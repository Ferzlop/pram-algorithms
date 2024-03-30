# EREW Search
```
function broadcast(a[n], x)
  a[0] = x
  for 1 <= i <= log_2(n) do
    for 2^(i-1) <= j < 2^i do in parallel
      a[j] = a[j-2^(i-1)]
  return a

function minima(a[n])
  for 1 <= i <= log_2(n) do
    for 0 <= j < n / (2i) do in parallel
      if a[2j] > a[2j+1] then
        a[j] = a[2j+1]
      else
        a[j] = a[2j]
  return a[0]

function erewSearch(l[n], x)
  temp[n]
  call broadcast(temp[n], x)
  for 0 <= i < n do in parallel
    if l[i] == temp[i] then
      temp[i] = i
    else
      temp[i] = INF
  return minima(temp[n])
```