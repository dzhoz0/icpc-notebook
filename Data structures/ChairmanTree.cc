// Born_To_Laugh - Hughie Do
#include <bits/stdc++.h>
#define alle(AC) AC.begin(), AC.end()
#define fi first
#define se second
using namespace std;
typedef long long ll;
[[maybe_unused]] const ll MOD = 998244353, INF = 1e9 + 7;
class Chairman_Tree
{
private:
    struct node{
        int l, r;
        int val;
        node(){
            l = 0;
            r = 0;
            val = 0;
        }
    };
    int n;
    vector<node> tree;
    int cntnode = 0;
    int build(int l, int r){
        int id = ++cntnode;
        if(l == r)return id;
        int mid = (l + r) >> 1;
        tree[id].l = build(l, mid);
        tree[id].r = build(mid+1, r);
        return id;
    }
    int Point_Update(int cur, int l, int r, int pos){
        int id = ++cntnode;
        if(l == r){
            tree[id].val = tree[cur].val + 1;
            return id;
        }
        tree[id].l = tree[cur].l;
        tree[id].r = tree[cur].r;
        int mid = (l + r) >> 1;
        if(pos <= mid){
            tree[id].l = Point_Update(tree[cur].l, l, mid, pos);
        }
        else{
            tree[id].r = Point_Update(tree[cur].r, mid + 1, r, pos);
        }
        tree[id].val = tree[tree[id].l].val + tree[tree[id].r].val;
        return id;
    }
    int get(int id, int l, int r, int lo, int hi){
        if(l > hi || r < lo)return 0;
        else if(l >= lo && r <= hi){
            return tree[id].val;
        }
        int mid = (l + r) >> 1;
        return get(tree[id].l, l, mid, lo, hi) + get(tree[id].r, mid + 1, r, lo, hi);
    }
    int walk(int l, int r, int a, int b, int c, int p, int x){
        if(l == r)return r;
        int sum = tree[tree[a].l].val + tree[tree[b].l].val
            - (tree[tree[c].l].val + tree[tree[p].l].val);
        int mid = (l + r) >> 1;
        if(sum >= x){
            return walk(l, mid, tree[a].l, tree[b].l, tree[c].l, tree[p].l, x);
        }
        else{
            return walk(mid + 1, r, tree[a].r, tree[b].r, tree[c].r, tree[p].r, x - sum);
        }
    }
public:
    int init(int len){
        n = len;
        tree.assign(20 * n, node());
        return build(1, n);
    }
    int Point_Update(int root, int pos){
        return Point_Update(root, 1, n, pos);
    }
    int get(int root, int l, int r){
        return get(root, 1, n, l, r);
    }
    int qr(int a, int b, int c, int p, int x){
        return walk(1, n, a, b, c, p, x);
    }
};
const int maxn = 1e5 + 10;
Chairman_Tree ct;
int ver[maxn], num[maxn], dep[maxn];
int binlift[maxn][20], parr[maxn];
vector<int> adj[maxn];
int n, q;
void dfs(int a, int par){
    ver[a] = ct.Point_Update(ver[par], num[a]);
    parr[a] = par;
    dep[a] = dep[par] + 1;
    for(auto &elm: adj[a]){
        if(elm == par)continue;
        binlift[elm][0] = a;
        for(int i=1; i<20; ++i){
            binlift[elm][i] = binlift[binlift[elm][i-1]][i-1];
        }
        dfs(elm, a);
    }
}
int lca(int a, int b){
    if(dep[a] < dep[b])swap(a, b);
    int k = dep[a] - dep[b];
    for(int i=0; i<20; ++i){
        if(k & (1 << i))a = binlift[a][i];
    }
    if(a == b)return a;
    for(int i=19; i>=0; --i){
        if(binlift[a][i] != binlift[b][i]){
            a = binlift[a][i];
            b = binlift[b][i];
        }
    }
    return binlift[a][0];
}
void solve(){
    cin >> n >> q;
    vector<int> temp;
    for(int i=1; i<=n; ++i){
        cin >> num[i];
        temp.push_back(num[i]);
    }
    sort(alle(temp));
    temp.erase(unique(alle(temp)), temp.end());
    for(int i=1; i<=n; ++i){
        num[i] = lower_bound(alle(temp), num[i]) - temp.begin() + 1;
    }
    for(int i=1; i<n; ++i){
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ver[0] = ct.init(temp.size() + 3);
    dfs(1, 0);
    while(q--){
        int a, b, x;cin >> a >> b >> x;
        int c = lca(a, b);
        int ans = ct.qr(ver[a], ver[b], ver[c], ver[parr[c]], x);
        cout << temp[ans - 1] << "\n";
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
