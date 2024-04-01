# EREW Sum
```
for 1 <= i <= log_2(n) do
  for-each 1 <= j <= n/2 do in parallel
    if 2j % 2^(i) == 0 do
      a[2j - 1] += a[(2j - 1) - 2^(i - 1)]
  endfor-each  
endfor
```
