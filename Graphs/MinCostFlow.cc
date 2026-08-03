struct MinCostFlow
{
    struct edge
    {
        int x, y;
        ll c, f, w;
    };
    int n, s, t;
    vector<edge> e;
    vector<int> trace;
    vector<vector<int>> adj;
    vector<ll> pi, dist;
    bool havneg = 0;

    void init(int a, int b, int c){
        n = a;
        s = b;
        t = c;
        havneg = 0;
        adj.assign(n + 1, vector<int> ());
        pi.assign(n + 1, 0);
        trace.assign(n + 1, 0);
        dist.assign(n + 1, 0);
        e.clear();
    }
    void adde(int x, int y, int c, int w){
        adj[x].push_back(e.size());
        e.push_back({x, y, c, 0, w});
        adj[y].push_back(e.size());
        e.push_back({y, x, 0, 0, -w});
        havneg |= (w < 0);
    }
    void setpi(){
        for(int i=1; i<=n; ++i) pi[i] = INF;
        pi[s] = 0;
        for(int i=1; i<=n; ++i){
            bool upd = 0;
            for(auto &elm: e){
                if(elm.c == elm.f) continue;
                if(pi[elm.x] == INF) continue;
                if(pi[elm.y] > pi[elm.x] + elm.w){
                    pi[elm.y] = pi[elm.x] + elm.w;
                    upd = 1;
                }
            }
            if(!upd) break;
            assert(i != n);
        }
    }
    void dijkstra(){
        for(int i=1; i<=n; ++i) dist[i] = INF;
        for(int i=1; i<=n; ++i) trace[i] = -1;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while(!pq.empty()){
            int x = pq.top().se;
            ll d = pq.top().fi;
            pq.pop();
            if(d > dist[x]) continue;
            for(auto &id: adj[x]){
                edge &elm = e[id];
                if(elm.c == elm.f) continue;

                ll wei = elm.w + pi[elm.x] - pi[elm.y];
                if(dist[elm.y] > dist[elm.x] + wei){
                    dist[elm.y] = dist[elm.x] + wei;
                    trace[elm.y] = id;
                    pq.push({dist[elm.y], elm.y});
                }
            }
        }
    }
    pair<ll, ll> mcflow(ll lim){//{mincost, fl} with fl <= lim
        if(havneg) setpi();
        pair<ll, ll> ans = {0, 0};
        while(lim){
            dijkstra();
            if(trace[t] == -1) break;
            ll f = lim;

            int y = t;
            while(y != s){
                int id = trace[y];
                f = min(f, e[id].c - e[id].f);
                y = e[id].x;
            }
            y = t;
            while(y != s){
                int id = trace[y];
                ans.fi += e[id].w * f;
                e[id].f += f;
                e[id ^ 1].f -= f;
                y = e[id].x;
            }
            ans.se += f;
            lim -= f;
            for(int i=1; i<=n; ++i) pi[i] = min(pi[i] + dist[i], INF);
        }
        return ans;
    }
};
