// Fat-Path Edmonds-Karp
// O(m * m * log(n) * log(maxflow))
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
    ans = 0;
    while(1){
        find_path();
        if(!trace[t]) break;
        updans();
    }
    cout << ans << '\n';
}
