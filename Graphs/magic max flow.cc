const int N = 1000 + 5;
const int MAXA = 1e9;
 
int a[N][N];
int n, m, p[N];
bool f[N];
 
int bfs(){
    memset(f, 0, sizeof f);
    memset(p, 0, sizeof p);
    f[1] = true; 
    queue <pair<int, int>> q;
    q.push({1, MAXA});
    while (!q.empty()){
        pair<int, int> st = q.front(); q.pop();
        int u = st.first, val = st.second;
 
        for(int v = 1; v <= n; ++v){
            if (!f[v] && a[u][v]){
                q.push({v, min(val, a[u][v])});
                f[v] = true; p[v] = u;
 
                if (v == n) return min(val, a[u][v]);
            }
        }
    }
    return 0;
}
 
int max_flow(){
    int ans = 0, flow = 0;
    while ((flow = bfs())){
        ans += flow;
        int u = n;
        while (u != 1){
            a[p[u]][u] -= flow;
            a[u][p[u]] += flow;
 
            u = p[u];
        }
    }
    return ans;
}
 
void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int u, v, w; cin >> u >> v >> w;
        a[u][v] += w;
    }
 
    cout << max_flow();
}

