# CREW Matrix Multiplication
```
for 0 <= i, j, k < n do in parallel
  c[i,j,k] = a[i,k] * b[k,j]

for 1 <= l <= log_2(n)
  for 0 <= i, j < n AND 1 <= k <= n/2 do in parallel
    if 2k % 2l == 0 then
      c[i,j,2k-1] += c[i,j,2k-1-2^(l-1)]
```