const int N = 100100;

vector<int> G[N];
int seen[N], iteration = 0;
int dist[N], matchL[N], matchR[N];

bool dfs(int u) {
    if(seen[u] == iteration) return 0;
    seen[u] = iteration;

    for(int v : G[u])
        if(matchR[v] == -1) {
            matchL[u] = v; matchR[v] = u;
            return 1;
        }

    for(int v : G[u])
        if(dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v])) {
            matchL[u] = v; matchR[v] = u;
            return 1;
        }

    return 0;
}

int matching(int M, int N, vector<pair<int, int>> E) {
    fill(matchL + 1, matchL + M + 1, -1);
    fill(matchR + 1, matchR + N + 1, -1);

    for(int i = 0; i < (int) E.size(); ++i) {
        int u = E[i].first, v = E[i].second;
        G[u].push_back(v);
    }

    int ans = 0;
    while(true) {
        queue<int> q;
        for(int u = 1; u <= M; ++u) {
            if(matchL[u] == -1) {
                dist[u] = 0; q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int v : G[u]) {
                if(matchR[v] != -1 && dist[matchR[v]] == -1) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }

        int newMatches = 0;
        ++iteration;
        for(int u = 1; u <= M; ++u) {
            if(matchL[u] == -1) newMatches += dfs(u);
        }
        if(newMatches == 0) break;
        ans += newMatches;
    }

    return ans;
}
