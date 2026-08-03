/*
 * Largest k so that n! is divisible by p^k
 * If k is prime then use algorithim below
 * If not, we have k = k = k_1^{p_1} \cdot \ldots \cdot k_m^{p_m}
 * Then the answer will be min(highest_exponent(k_i, n) / p_i) with i = 1...m
*/
int highest_exponent(int p, const int &n){
  int ans = 0;
  int t = p;
  while(t <= n){
    ans += n/t;
    t*=p;
  }
  return ans;
}
