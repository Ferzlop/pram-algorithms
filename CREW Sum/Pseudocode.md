# CREW Sum
```
for 1 <= i <= log_2(n)
  a_copy = a
  for-each 2^(i-1) <= j < n do in parallel
    a[j] += a_copy[j - 2^(i - 1)]
  endfor-each
endfor
```