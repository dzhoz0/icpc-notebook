// Born_To_Laugh - Hughie Do
#include <bits/stdc++.h>
#define alle(AC) AC.begin(), AC.end()
using namespace std;
typedef long long ll;
[[maybe_unused]] const ll MOD = 998244353, INF = 1e9 + 7;
 
const int maxn = 1e5 + 10;
int n, m;
vector<int> adj[maxn];
vector<int> scadj[maxn];
int del[maxn], tin[maxn], low[maxn];
int num[maxn];
ll comsum[maxn], dp[maxn];
int incom[maxn];
int cc = 0;
int id = 0;
vector<int> st, topo;
void dfs(int a){
    tin[a] = low[a] = ++id;
    st.push_back(a);
    for(auto &elm: adj[a]){
        if(del[elm])continue;
        if(tin[elm]){
            low[a] = min(low[a], tin[elm]);
            continue;
        }
        dfs(elm);
        low[a] = min(low[a], low[elm]);
    }
    if(low[a] == tin[a]){
        cc++;
        while(!del[a]){
            del[st.back()] = 1;
            incom[st.back()] = cc;
            comsum[cc] += num[st.back()];
            st.pop_back();
        }
    }
}
void dfstopo(int a){
    // cout << a << ' ';
    del[a] = 1;
    for(auto &elm: scadj[a]){
        if(del[elm])continue;
        // cout << a << ' ' << elm << "\n";
        dfstopo(elm);
    }
    // cout << "\n\n";
    topo.push_back(a);
}
void solve(){
    cin >> n >> m;
    for(int i=1; i<=n; ++i)cin >> num[i];
    for(int i=1; i<=m; ++i){
        int a, b;cin >> a >> b;
        adj[a].push_back(b);
    }
    for(int i=1; i<=n; ++i){
        if(!tin[i])dfs(i);
    }
    for(int i=1; i<=n; ++i){
        for(auto &elm: adj[i]){
            if(incom[i] != incom[elm]){
                scadj[incom[i]].push_back(incom[elm]);
            }
        }
        del[i] = 0;
    }
 
    for(int i=1; i<=cc; ++i){
        if(!del[i])dfstopo(i);
    }
    reverse(alle(topo));
    ll ans = 0;
    for(auto &i: topo){
        dp[i] = max(dp[i], comsum[i]);
        for(auto &elm: scadj[i]){
            dp[elm] = max(dp[elm], dp[i] + comsum[elm]);
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
