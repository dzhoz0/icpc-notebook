// Born_To_Laugh - Hughie Do
#include <bits/stdc++.h>
#define alle(sth) sth.begin(), sth.end()
using namespace std;
typedef long long ll;
[[maybe_unused]] const int MOD = 998244353, INF = 1e9 + 7;
const int MAXN = 2;
#define int ll
class Matrix
{
public:
    int row, col;
    vector<vector<int>> val;
    //val[row][col]
    Matrix(int a = MAXN, int b = MAXN):
        row(a), col(b), val(a, vector<int> (b, 0)){}

    static Matrix base(int s){
        Matrix a(s, s);
        for(int i=0; i<s; ++i){
            a.val[i][i] = 1;
        }
        return a;
    }
    void init(vector<vector<int>> b){
        row = b.size();
        col = b[0].size();
        val = b;
    }

    Matrix operator *(const Matrix& b){
        Matrix c(row, b.col);
        for(int i=0; i<row; ++i){
            for(int j=0; j<b.col; ++j){
                for(int x=0; x<col; ++x){//col = b.row
                    c.val[i][j] += (ll)val[i][x] * b.val[x][j];
                    c.val[i][j] %= INF;
                }
            }
        }
        return c;
    }
};
Matrix powmod(Matrix a, int b){
    Matrix ans = Matrix::base(a.row);
    while(b){
        if(b&1){
            ans = ans*a;
        }
        a = a*a;
        b = b >> 1;
    }
    return ans;
}
void solve(){
    Matrix sth;
    sth.init({
        {0, 1},
        {1, 1}
    });
    int n;cin >> n;
    sth = powmod(sth, n-2);
    if(n <= 2){
        cout << 1 << '\n';
        return;
    }
    Matrix ans;
    ans.init({
        {1, 1}
    });
    ans = ans * sth;
    cout << ans.val[0][1];
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
