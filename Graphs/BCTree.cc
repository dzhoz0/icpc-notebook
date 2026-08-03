const int maxn = 2e5 + 10;
int tin[maxn], low[maxn], sz[maxn];
vector<int> adj[maxn], bcadj[maxn], st;
int id = 0, cc = 0, ccsz = 0, ans = 0, n, m;

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
