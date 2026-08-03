/**
SOD(n) = sum of actual divisors, CSOD(n) = sod(1) + sod(2) + ... + sod(n)
*/

long long csod(long long n) {
  long long ans = 0;
  for (long long i = 2; i * i <= n; ++i) {
    long long j = n / i;
    ans += (i + j) * (j - i + 1) / 2;
    ans += i * (j - i);
  }
  return ans;
}

