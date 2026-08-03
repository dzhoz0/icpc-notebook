// O(m * min(n ^ (2 / 3), m ^ (1 / 2)) neu moi c = 1
// O(m * n * n)
struct Dinic
{
    struct edge{
        int x, y;
        ll c, f;
        edge(int a = 0, int b = 0, ll z = 0, ll u = 0){
            x = a;
            y = b;
            c = z;
            f = u;
        }
    };

    int n, s, t;
    vector<int> d, pt;
    vector<edge> e;
    vector<vector<int>> adj;
    
    void init(int len, int a, int b){
        s = a;
        t = b;
        n = len;
        adj.assign(n + 1, vector<int> ());
        d.assign(n + 1, 0);
        pt.assign(n + 1, 0);
        e.clear();
    }
    void adde(int a, int b, ll c){
        adj[a].push_back(e.size());
        e.push_back(edge(a, b, c, 0));
        adj[b].push_back(e.size());
        e.push_back(edge(b, a, 0, 0));
    }
    int bfs(){
        for(int i=1; i<=n; ++i) d[i] = 0;
        deque<int> bfs;
        bfs.push_back(s);
        d[s] = 1;
        while(!bfs.empty()){
            int x = bfs.front();
            bfs.pop_front();
            for(auto &id: adj[x]){
                edge& elm = e[id];
                int y = elm.y;
                if(d[y] != 0 || elm.c == elm.f) continue;
                d[y] = d[x] + 1;
                bfs.push_back(y);
            }
        }
        return d[t];
    }
    ll dfs(int a, ll val){
        if(a == t || val == 0) return val;
        for(; pt[a] < adj[a].size(); pt[a]++){
            int id = adj[a][pt[a]];
            int b = e[id].y;
            
            if(d[b] != d[a] + 1) continue;
            if(e[id].c == e[id].f) continue;

            ll nxt = dfs(b, min(val, e[id].c - e[id].f));
            if(nxt == 0) continue;
            e[id].f += nxt;
            e[id ^ 1].f -= nxt;
            return nxt;
        }
        return 0;
    }
    ll maxflow(){
        ll ans = 0;
        while(bfs()){
            for(int i=1; i<=n; ++i) pt[i] = 0;
            while(ll val = dfs(s, INF)) ans += val;
        }
        return ans;
    }
};

int n, m, s, t;
Dinic fl;

void solve(){
    cin >> n >> m >> s >> t;
    fl.init(n, s, t);
    for(int i=1; i<=m; ++i){
        int a, b;ll c;
        cin >> a >> b >> c;
        fl.adde(a, b, c);
    }
    cout << fl.maxflow() << '\n';
}

