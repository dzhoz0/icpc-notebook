const int maxn = 1e5 + 10;
int n, m, cc = 0, id = 0;
vector<int> adj[maxn], scadj[maxn];
int del[maxn], tin[maxn], low[maxn], num[maxn], incom[maxn];
ll comsum[maxn], dp[maxn];
vector<int> st;
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
