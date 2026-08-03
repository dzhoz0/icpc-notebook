/*
 Finds the min mean cycle, if you need the max mean cycle
 just add all the edges with negative cost and print ans * -1
 O(N * M)
 */
const long long INF = 4e18;

struct Edge {
    int to;
    long long w;
};

double karp(vector<vector<Edge>> g) {
    int n = g.size();

    // Super source
    g.push_back({});
    for (int i = 0; i < n; i++)
        if (!g[i].empty())
            g[n].push_back({i, 0});
    n++;

    vector<vector<long long>> dp(n + 1, vector<long long>(n, INF));
    dp[0][n - 1] = 0;

    // dp[k][v] = shortest path to v using exactly k edges
    for (int k = 1; k <= n; k++)
        for (int u = 0; u < n; u++)
            if (dp[k - 1][u] != INF)
                for (auto [v, w] : g[u])
                    dp[k][v] = min(dp[k][v], dp[k - 1][u] + w);

    double ans = 1e100;
    bool hasCycle = false;

    for (int v = 0; v < n - 1; v++) {
        if (dp[n][v] == INF) continue;
        hasCycle = true;

        double cur = -1e100;
        for (int k = 0; k < n; k++)
            if (dp[k][v] != INF)
                cur = max(cur, (double)(dp[n][v] - dp[k][v]) / (n - k));

        ans = min(ans, cur);
    }

    if (!hasCycle) return numeric_limits<double>::infinity();
    return ans;
}
