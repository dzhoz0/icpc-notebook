// Born_To_Laugh - Hughie Do
#include <bits/stdc++.h>
#define alle(AC) AC.begin(), AC.end()
using namespace std;
typedef long long ll;
[[maybe_unused]] const ll MOD = 998244353, INF = 1e9 + 7;
const int maxn = 5e4 + 10;
class segtree
{
private:
    int n;
    vector<int> tree;
    vector<int> lazy;
    void operate(int id, int l, int r){
        if(!lazy[id])return;
        tree[id] += lazy[id];
        if(l != r){
            lazy[id << 1] += lazy[id];
            lazy[id << 1|1] += lazy[id];
        }
        lazy[id] = 0;
    }
    void upd(int id, int l, int r, int lo, int hi, int val){
        operate(id, l, r);
        if(l > hi || r < lo)return;
        else if(l >= lo && r <= hi){
            lazy[id] += val;
            operate(id, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        upd(id << 1, l, mid, lo, hi, val);
        upd(id << 1|1, mid+1, r, lo, hi, val);
        tree[id] = max(tree[id << 1], tree[id << 1|1]);
    }
public:
    segtree(){
        n = maxn;
        tree.assign(n << 2, 0);
        lazy.assign(n << 2, 0);
    }
    void upd(int lo, int hi){
        upd(1, 1, n, lo, hi, 1);
    }
    int get(){
        return tree[1];
    }
};
segtree st;
int n, q;
vector<int> adj[maxn];
int tin[maxn], chain[maxn], head[maxn], parr[maxn], big[maxn], dep[maxn], sz[maxn];
int id = 0;
int cur = 1;
void predfs(int a, int par){
    sz[a] = 1;
    for(auto &elm: adj[a]){
        if(elm == par)continue;
        dep[elm] = dep[a] + 1;
        predfs(elm, a);
        sz[a] += sz[elm];
        if(sz[elm] > sz[big[a]])big[a] = elm;
    }
}
void hld(int a, int par, int root){
    tin[a] = ++id;
    chain[a] = cur;
    parr[a] = par;
    head[a] = root;
    if(big[a])hld(big[a], a, root);
    for(auto &elm: adj[a]){
        if(elm == par || elm == big[a])continue;
        cur++;
        hld(elm, a, elm);
    }
}
int lca(int a, int b){
    while(chain[a] != chain[b]){
        if(chain[a] < chain[b])swap(a, b);
        a = parr[head[a]];
    }
    if(dep[a] > dep[b])swap(a, b);
    return a;
}
void ope(int a, int b){
    int c = lca(a, b);
    // cout << a << ' ' << b << ' ' << c << '\n';
    // return;
    // int c = 0;
    while(chain[a] != chain[c]){
        st.upd(tin[head[a]], tin[a]);
        a = parr[head[a]];
    }
    while(chain[b] != chain[c]){
        st.upd(tin[head[b]], tin[b]);
        b = parr[head[b]];
    }
    if(dep[a] > dep[b])swap(a, b);
    st.upd(tin[a], tin[b]);
}
void solve(){
    cin >> n >> q;
    for(int i=1; i<n; ++i){
        int a, b;cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    predfs(1, -1);
    hld(1, -1, 1);
    for(int i=1; i<=q; ++i){
        int a, b;cin >> a >> b;
        ope(a, b);
    }
    cout << st.get();
}
signed main(){
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
