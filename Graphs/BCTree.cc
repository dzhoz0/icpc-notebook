// Born_To_Laugh - Hughie Do
#include <bits/stdc++.h>
#define alle(Lotus) Lotus.begin(), Lotus.end()
using namespace std;
typedef long long ll;
[[maybe_unused]] const ll MOD = 998244353, INF = 1e9 + 7;
#define int ll
const int maxn = 2e5 + 10;
int tin[maxn], low[maxn], sz[maxn];
vector<int> adj[maxn], bcadj[maxn], st;
int id = 0, cc = 0;
int ccsz = 0;
int ans = 0;
int n, m;
void dfs(int a, int par){
    tin[a] = low[a] = ++id;
    ccsz++;
    st.push_back(a);
    for(auto &elm: adj[a]){
        if(elm == par)continue;
        if(tin[elm]){
            low[a] = min(low[a], tin[elm]);
            continue;
        }
        dfs(elm, a);
        low[a] = min(low[a], low[elm]);

        if(low[elm] >= tin[a]){
            cc++;
            bcadj[a].push_back(cc);
            bcadj[cc].push_back(a);
            // cout << cc << '\n';
            while(bcadj[cc].empty() || bcadj[cc].back() != elm){
                bcadj[cc].push_back(st.back());
                bcadj[st.back()].push_back(cc);
                st.pop_back();
            }
        }
    }
}
void bctree(int a, int par){
    sz[a] = (a <= n);
    for(auto &elm: bcadj[a]){
        if(elm == par)continue;
        bctree(elm, a);
        sz[a] += sz[elm];
        if(a > n){
            //a = bcc
            ans -= (bcadj[a].size() - 1) * sz[elm] * (sz[elm] - 1);
        }
    }
    if(a > n){
        int num = ccsz - sz[a];
        ans -= num * (num - 1) * (bcadj[a].size() - 1);
    }
}
void solve(){
    cin >> n >> m;
    cc = n;
    for(int i=1; i<=m; ++i){
        int a, b;cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(int i=1; i<=n; ++i){
        if(!tin[i]){
            ccsz = 0;
            dfs(i, -1);
            ans += ccsz * (ccsz - 1) * (ccsz - 2);
            bctree(i, -1);
        }
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
