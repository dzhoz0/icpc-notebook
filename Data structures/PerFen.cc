// Born_To_Laugh - Hughie Do
#include <bits/stdc++.h>
#define alle(AC) AC.begin(), AC.end()
#define fi first
#define se second
using namespace std;
typedef long long ll;
[[maybe_unused]] const int MOD = 998244353, INF = 1e9 + 7;
const int maxn = 2e5 + 10;

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

int n, k;
int a[maxn], b[maxn], t[maxn];
int prefsum[maxn * 2];
int ver[maxn];
PerFen ft;
vector<int> temp;

void solve(){
    cin >> n >> k;
    for(int i=1; i<=n; ++i){
        cin >> a[i] >> b[i];
        temp.push_back(a[i]);
        temp.push_back(b[i]);
    }
    for(int i=1; i<=k; ++i){
        cin >> t[i];
        temp.push_back(t[i]);
    }
    sort(alle(temp));
    temp.erase(unique(alle(temp)), temp.end());
    ft.init(temp.size() + 5);

    for(int i=1; i<=n; ++i){
        a[i] = lower_bound(alle(temp), a[i]) - temp.begin() + 1;
        b[i] = lower_bound(alle(temp), b[i]) - temp.begin() + 1;
    }
    for(int i=1; i<=k; ++i){
        t[i] = lower_bound(alle(temp), t[i]) - temp.begin() + 1;
    }
    for(int i=k; i>=1; --i) ver[i] = ft.upd(t[i], 1);

    auto check = [&](int x, int a, int b) -> bool {
        return ft.qr(a, b - 1, ver[x]) == 0;
    };

    ll ans = 0;
    for(int i=1; i<=n; ++i){
        if(ft.qr(min(a[i], b[i]), max(a[i], b[i]) - 1, ver[1]) == 0){
            int num = ft.qr(max(a[i], b[i]), ft.n, ver[1]);
            if(num & 1){
                ans += temp[b[i] - 1];
            }
            else ans += temp[a[i] - 1];
            continue;
        }

        int lo = 1, hi = k;
        int res = hi;
        while(hi >= lo){
            int mid = (lo + hi) >> 1;
            if(check(mid, min(a[i], b[i]), max(a[i], b[i]))){
                res = mid;
                hi = mid - 1;
            }
            else lo = mid + 1;
        }
        
        int num = ft.qr(max(a[i], b[i]), ft.n, ver[res]);
        if(num & 1){
            ans += temp[min(a[i], b[i]) - 1];
        }
        else{
            ans += temp[max(a[i], b[i]) - 1];
        }
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
