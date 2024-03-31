# CREW Matrix Multiplication
```
for 0 <= i, j, k < n do in parallel
  c[i,j,k] = a[i,k] * b[k,j]

for 0 <= i, j < n AND 1 <= k < n do in parallel
  c[i][j][0] += a[i][j][k]
```