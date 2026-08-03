void predfs(int a, int par){
    sz[a] = 1;
    for(auto &elm: adj[a]){
        if(elm == par)continue;
        dep[elm] = dep[a] + 1;
        predfs(elm, a);
        sz[a] += sz[elm];
        if(sz[elm] > sz[big[a]])big[a] = elm;
    }
}
void hld(int a, int par, int root){
    tin[a] = ++id;
    chain[a] = cur;
    parr[a] = par;
    head[a] = root;
    if(big[a])hld(big[a], a, root);
    for(auto &elm: adj[a]){
        if(elm == par || elm == big[a])continue;
        cur++;
        hld(elm, a, elm);
    }
}
int lca(int a, int b){
    while(chain[a] != chain[b]){
        if(chain[a] < chain[b])swap(a, b);
        a = parr[head[a]];
    }
    if(dep[a] > dep[b])swap(a, b);
    return a;
}
void ope(int a, int b){
    int c = lca(a, b);
    while(chain[a] != chain[c]){
        st.upd(tin[head[a]], tin[a]);
        a = parr[head[a]];
    }
    while(chain[b] != chain[c]){
        st.upd(tin[head[b]], tin[b]);
        b = parr[head[b]];
    }
    if(dep[a] > dep[b])swap(a, b);
    st.upd(tin[a], tin[b]);
}
