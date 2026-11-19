struct PerFen
{
    int n, time;
    vector<vector<pair<int, int>>> bit;
    void init(int len){
        n = len;
        time = 0;
        bit.assign(len + 1, {{0, 0}});
    }
    int upd(int pos, int val){
        time++;
        for(; pos<=n; pos += pos & -pos){
            bit[pos].push_back({time, bit[pos].back().se + val});
        }
        return time;
    }
    int qr(int pos, int tim){
        int ans = 0;
        for(; pos>0; pos -= pos & -pos){
            int id = upper_bound(alle(bit[pos]), make_pair(tim, INF)) - bit[pos].begin() - 1;
            ans += bit[pos][id].se;            
        }
        return ans;
    }
    int qr(int l, int r, int pos){
        if(l > r) return 0;
        return qr(r, pos) - qr(l - 1, pos);
    }
};
