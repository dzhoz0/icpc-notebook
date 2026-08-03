typedef long long ll;
typedef unsigned long long ull;

struct Factorizer
{
    ull mul_mod(ull a, ull b, ull m){
        ull res = 0;
        a %= m;
        while(b > 0){
            if(b & 1) res = (res + a) % m;
            a = (a + a) % m;
            b >>= 1;
        }
        return res;
    }
    ull modpow(ull base, ull exp, ull mod){
        ull res = 1;
        base %= mod;
        while(exp > 0){
            if(exp & 1) res = mul_mod(res, base, mod);
            base = mul_mod(base, base, mod);
            exp >>= 1;
        }
        return res;
    }
    bool is_prime(ull n){
        if(n < 2) return false;
        if(n == 2 || n == 3) return true;
        if(n % 2 == 0) return false;
        ull d = n - 1;
        int s = 0;
        while((d & 1) == 0){
            d >>= 1;
            s++;
        }
        static const ull bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        for(ull a : bases){
            if(n <= a) break;
            ull x = modpow(a, d, n);
            if(x == 1 || x == n - 1) continue;
            bool composite = true;
            for(int r = 1; r < s; r++){
                x = mul_mod(x, x, n);
                if(x == n - 1){
                    composite = false;
                    break;
                }
            }
            if(composite) return false;
        }
        return true;
    }
    ull pollard_rho(ull n){
        if(n % 2 == 0) return 2;
        if(is_prime(n)) return n;
        ull x = 2, y = 2, d = 1, c = 1;
        auto f = [&](ull x, ull n, ull c){
            return (mul_mod(x, x, n) + c) % n;
        };
        while(d == 1){
            x = f(x, n, c);
            y = f(f(y, n, c), n, c);
            ull diff = (x > y) ? (x - y) : (y - x);
            d = gcd(diff, n);
            if(d == n){
                x = rand() % (n - 2) + 2;
                y = x;
                c = rand() % (n - 1) + 1;
                d = 1;
            }
        }
        return d;
    }
    void factorize_helper(ull n, vector<ull>& primes){
        if(n <= 1) return;
        if(is_prime(n)){
            primes.push_back(n);
            return;
        }
        ull divisor = pollard_rho(n);
        factorize_helper(divisor, primes);
        factorize_helper(n / divisor, primes);
    }
    vector<pair<ll, int>> get_factors(ll n){
        vector<ull> primes;
        factorize_helper(n, primes);
        sort(alle(primes));
        vector<pair<ll, int>> factors;
        for(ull p : primes){
            if(!factors.empty() && factors.back().fi == (ll)p){
                factors.back().se++;
            } else {
                factors.push_back({(ll)p, 1});
            }
        }
        return factors;
    }
};

// Usage: Factorizer fact; vector<pair<ll, int>> fact.get_factors(n)

