void pre_dfs(int a, int par){
    for(auto &sth: adj[a]){
        int elm = sth.first;
        int wei = sth.second;
        if(elm == par)continue;
        dep[elm] = dep[a] + 1;
        bitm[elm] = lat_bit(bitm[a], wei);
        pre_dfs(elm, a);
        sz[a] += sz[elm];
        if(bigchild[a] == -1 || sz[bigchild[a]] < sz[elm])bigchild[a] = elm;
    }
}

void calc(int a, int par, int root){
    for(auto &sth: adj[a]){
        int elm = sth.first;
        if(elm == par)continue;
        calc(elm, a, root);
    }

    int sth = bitm[a];
    if(besdep[sth] != -1){
        ans[root] = max(ans[root], besdep[sth] + dep[a] - 2 * dep[root]);
    }
    for(int i=0; i<22; ++i){
        sth = lat_bit(bitm[a], i);
        if(besdep[sth] != -1){
            ans[root] = max(ans[root], besdep[sth] + dep[a] - 2 * dep[root]);
        }
    }
}

void add(int a, int par, bool godown){
    if(besdep[bitm[a]] == -1) clearlist.push_back(bitm[a]);
    besdep[bitm[a]] = max(besdep[bitm[a]], dep[a]);

    if(!godown)return;
    for(auto &sth: adj[a]){
        int elm = sth.first;
        if(elm == par)continue;
        add(elm, a, 1);
    }
}
void cleardata(){
    for(auto &elm: clearlist){
        besdep[elm] = -1;
    }
    clearlist.clear();
}
void dfs(int a, int par){
    for(auto &sth: adj[a]){
        int elm = sth.first;
        if(elm == par || elm == bigchild[a])continue;
        dfs(elm, a);
        cleardata();
        ans[a] = max(ans[a], ans[elm]);
    }

    if(bigchild[a] != -1){
        dfs(bigchild[a], a);
        ans[a] = max(ans[a], ans[bigchild[a]]);
    }

    for(auto &sth: adj[a]){
        int elm = sth.first;
        if(elm == par || elm == bigchild[a])continue;
        calc(elm, a, a);
        add(elm, a, 1);
    }

    int root = a;
    int sth = bitm[a];
    if(besdep[sth] != -1){
        ans[root] = max(ans[root], besdep[sth] + dep[a] - 2 * dep[root]);
    }
    for(int i=0; i<22; ++i){
        sth = lat_bit(bitm[a], i);
        if(besdep[sth] != -1){
            ans[root] = max(ans[root], besdep[sth] + dep[a] - 2 * dep[root]);
        }
    }

    add(a, par, 0);
}
