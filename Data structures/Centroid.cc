const int maxn = 1e5 + 10;
int n, q;
vector<int> adj[maxn];
int dep[maxn], del[maxn], sz[maxn], binlift[maxn][20];
int paric[maxn];
vector<int> mintor(maxn, INF);

void predfs(int a, int par){
    sz[a] = 1;
    for(auto &elm: adj[a]){
        if(del[elm] || elm == par)continue;
        predfs(elm, a);
        sz[a] += sz[elm];
    }
}
int findcent(int a, int par, int root){
    for(auto &elm: adj[a]){
        if(elm == par || del[elm])continue;
        if(sz[elm] > sz[root]/2)return findcent(elm, a, root);
    }
    return a;
}
void decom(int a, int par){
    predfs(a, -1);
    int cent = findcent(a, -1, a);
    del[cent] = 1;
    paric[cent] = par;
    for(auto &elm: adj[cent]){
        if(del[elm])continue;
        decom(elm, cent);
    }
}
void ope1(int a){
    int b = a;
    while(b != -1){
        mintor[b] = min(mintor[b], getdist(a, b));
        b = paric[b];
    }
}
int ope2(int a){
    int b = a;
    int ans = INF;
    while(b != -1){
        ans = min(ans, getdist(a, b) + mintor[b]);
        b = paric[b];
    }
    return ans;
}
