struct Point {
    int x, y;
    Point() {
        x = 0;
        y = 0;
    }
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point operator - (const Point &o) const {
        return Point(x - o.x, y - o.y);
    }
    Point operator + (const Point &o) const {
        return Point(x + o.x, y + o.y);
    }
    bool operator < (const Point &o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator == (const Point &o) const {
        return (x == o.x && y == o.y);
    }
};

struct Line {
    long long A, B, C;
    Line() {
        A = 0;
        B = 0;
        C = 0;
    }
    Line(Point x, Point y) {
        A = x.y - y.y;
        B = y.x - x.x;
        C = x.y * y.x - x.x * y.y;
    }
};

int cross_product(Point u, Point v) {
    return u.x * v.y - u.y * v.x;
}

int dot_product(Point u, Point v) {
    return u.x * v.x + u.y * v.y;
}

// 2 x Sabc = |ab x ac|
int area_triangle(Point a, Point b, Point c) {
    Point ab = b - a;
    Point ac = c - a;
    return abs(cross_product(ab, ac));
}

bool is_ccw(Point a, Point b, Point c) {
    Point ab = b - a;
    Point ac = c - a;
    return cross_product(ab, ac) > 0;
    // ccw: val > 0
    // cw: val < 0
    // collinear: val = 0
}

int angle_type(Point a, Point b, Point c) {
    // checking angle type of bac
    Point ab = b - a;
    Point ac = c - a;
    int x = dot_product(ab, ac);
    // obtuse
    if (x < 0) return 0;
    // right
    if (x == 0) return 1;
    // acute
    if (x > 0) return 2;
}
