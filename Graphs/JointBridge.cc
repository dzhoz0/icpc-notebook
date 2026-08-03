// Born_To_Laugh - Hughie Do
#include <bits/stdc++.h>
#define alle(Lotus) Lotus.begin(), Lotus.end()
using namespace std;
typedef long long ll;
[[maybe_unused]] const ll MOD = 998244353, INF = 1e9 + 7;
#define int ll
const int maxn = 1e4 + 10;
int n, m;
vector<int> adj[maxn];
int tin[maxn], tout[maxn], low[maxn];
int id = 0;
int cntj = 0, cntb = 0;
void dfs(int a, int par){
    id++;
    tin[a] = id;
    low[a] = id;
    bool ok = 0;
    int child = 0;
    for(auto &elm: adj[a]){
        if(elm == par)continue;
        if(tin[elm] == 0){
            child++;
            dfs(elm, a);
            low[a] = min(low[a], low[elm]);
         
            if(low[elm] == tin[elm])cntb++;

            ok |= (par != -1 && (low[elm] >= tin[a]));
        }
        else low[a] = min(low[a], tin[elm]);
    }
    ok |= (par == -1 && child > 1);
    if(ok) cntj++;
    tout[a] = id;
}
void solve(){
    cin >> n >> m;
    for(int i=1; i<=m; ++i){
        int a, b;cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(int i=1; i<=n; ++i){
        if(!tin[i])dfs(i, -1);
    }
    cout << cntj << ' ' << cntb;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
