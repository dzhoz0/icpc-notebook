struct Point {
    int x, y;
    Point(int ix = 0, int iy = 0) {
        x = ix;
        y = iy;
    }
};
 
bool cmp(Point a, Point b) {
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
 
Point vec(Point p1, Point p2) {
    Point res;
    res.x = p2.x - p1.x;
    res.y = p2.y - p1.y;
    return res;
}
 
int cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
 
int point_location(vector<Point> p) {
    int res = cross(vec(p[0], p[1]), vec(p[0], p[2]));
    if(res == 0) return 0;
    else if(res > 0) return -1; // left
    return 1; // right
}
 
void solve()
{
    int n; cin >> n;
    vector<Point> a(n);
    for(auto &it : a) cin >> it.x >> it.y;
    sort(a.begin(), a.end(), cmp);
    
    vector<Point> v1, v2;
    for(int i = 0; i < n; i++) {
        while(v1.size() >= 2 && point_location({v1[(int)v1.size() - 2], v1[(int)v1.size() - 1], a[i]}) == -1) v1.pop_back();
        v1.push_back(a[i]);
    }
    for(int i = n - 1; i >= 0; i--) {
        while(v2.size() >= 2 && point_location({v2[(int)v2.size() - 2], v2[(int)v2.size() - 1], a[i]}) == -1) v2.pop_back();
        v2.push_back(a[i]);
    }
 
    v1.pop_back();
    v2.pop_back();
 
    cout << v1.size() + v2.size() << '\n';
    for(auto v: {v1, v2}) {
        for(Point p : v) cout << p.x << ' ' << p.y << '\n';
    }
}
