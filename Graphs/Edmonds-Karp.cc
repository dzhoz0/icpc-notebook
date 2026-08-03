// Born_To_Laugh - Hughie Do
#include <bits/stdc++.h>
#define alle(AC) AC.begin(), AC.end()
#define fi first
#define se second
using namespace std;
typedef long long ll;
[[maybe_unused]] const ll MOD = 998244353, INF = 3e18 + 7;

// Fat-Path Edmonds-Karp
// O(m * m * log(n) * log(maxflow))

const int maxn = 1010;
ll ans;
int n, m, s, t;
ll c[maxn][maxn], f[maxn][maxn], trace[maxn];
vector<int> adj[maxn];

void find_path(){
    for(int i=1; i<=n; ++i) trace[i] = 0;
    vector<ll> max_cap(n + 1, 0); 

    priority_queue<pair<ll, int>> pq; 
    pq.push({INF, s});
    max_cap[s] = INF;
    trace[s] = -1;
    
    while(!pq.empty()){
        auto [cap, x] = pq.top();
        pq.pop();
        if(x == t) break; 
        if(cap < max_cap[x]) continue;
        for(auto &elm: adj[x]){
            ll residual = c[x][elm] - f[x][elm];
            if(residual == 0) continue;
            ll new_cap = min(cap, residual);
            if(new_cap > max_cap[elm]){
                max_cap[elm] = new_cap;
                trace[elm] = x;
                pq.push({new_cap, elm});
            }
        }
    }
}
void updans(){
    if(trace[t] == 0) return;
    int x = t;
    ll minn = INF;
    while(x != s){
        minn = min(minn, c[trace[x]][x] - f[trace[x]][x]);
        x = trace[x];
    }
    ans += minn;
    x = t;
    while(x != s){
        f[trace[x]][x] += minn;
        f[x][trace[x]] -= minn;
        x = trace[x];
    }
}

void solve(){
    cin >> n >> m >> s >> t;
    for(int i=1; i<=m; ++i){
        int x, y, z; cin >> x >> y >> z;
        adj[x].push_back(y);
        adj[y].push_back(x);
        c[x][y] += z;
    }
    ans = 0;
    while(1){
        find_path();
        if(!trace[t]) break;
        updans();
    }
    cout << ans << '\n';
}

signed main(){
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
