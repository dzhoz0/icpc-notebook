struct LineContainer
{
    struct line{
        ll a, b;
        mutable ll p;
        bool operator < (const line& o) const {
            if(o.a == INF && o.b == INF) return p < o.p;
            return a < o.a;
        }
    };
    multiset<line> lc;
    ll div(ll a, ll b){
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool phe(multiset<line>::iterator x, multiset<line>::iterator y){
        if(y == lc.end()){
            x->p = INF;
            return 0;
        }
        if(x->a == y->a){
            if(x->b >= y->b) x->p = INF;
            else x->p = -INF;
            return x->p >= y->p;
        }
        x->p = div(x->b - y->b, y->a - x->a);
        return x->p >= y->p;
    }
    void add(ll a, ll b){
        auto x = lc.insert({a, b, 0});
        auto y = next(x);
        while(phe(x, y)) y = lc.erase(y);
        if((y = x) != lc.begin() && phe(--x, y))
            phe(x, y = lc.erase(y));
        while((y = x) != lc.begin() && (--x)->p >= y->p)
            phe(x, y = lc.erase(y));
    }
    ll qr(ll x){
        assert(!lc.empty());
        line l = *lc.lower_bound({INF, INF, x});
        return l.a * x + l.b;
    }
};
