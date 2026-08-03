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
