std::vector<Point> minkowskiSum(std::vector<Point> a, std::vector<Point> b) {
    rotate(begin(a), min_element(begin(a), end(a)), end(a));
    rotate(begin(b), min_element(begin(b), end(b)), end(b));
    
    int n = a.size(), m = b.size();
    std::vector<Point> h(n + m + 1); h[0] = a[0] + b[0];
    int t = 1;
    
    for (int i = 0, j = 0; i < n || j < m; ) {
        if (i == n) j++;
        else if (j == m) i++;
        else {
            Point pa = a[(i + 1) % n] - a[i], pb = b[(j + 1) % m] - b[j];
            int cr = cross_product(pa, pb);
            if (cr >= 0) i++;
            if (cr <= 0) j++;
        }
        h[t++] = (a[i % n] + b[j % m]);
    }

    return std::vector<Point>(h.begin(), h.begin() + t - (t >= 2 && h[0] == h[t - 1]));
}
