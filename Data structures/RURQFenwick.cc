class Fenwick{
private:
    int n;
    vector<ll> bit1, bit2;
    void pupd(vector<ll> &b, int u, ll v) {
        int idx = u;
        while (idx <= n) {
            b[idx] += v;
            idx += (idx & (-idx));
        }
    }
    ll get(vector<ll> &b, int u) {
        int idx = u;
        ll ans = 0;
        while (idx > 0) {
            ans += b[idx];
            idx -= (idx & (-idx));
        }
        return ans;
    }
    ll pref(int u) {
        return get(bit1, u) - get(bit2, u) * (n - u);
    }
public:
    void init(int len){
        n = len;
        bit1.assign(n + 1, 0);
        bit2.assign(n + 1, 0);
    }
    void upd(int l, int r, ll v) {
        pupd(bit1, l, v * (n - l + 1));
        pupd(bit1, r + 1, v * (r - n));
        pupd(bit2, l, v);
        pupd(bit2, r + 1, -v);
    }
    ll qr(int l, int r) {
        return pref(r) - pref(l - 1);
    }
};
