// is_cw here returns cross_product <= 0, NOT strictly < 0
std::vector<Point> getHull(std::vector<Point> &p) {
    int n = p.size();
    sort(p.begin(), p.end());

    std::vector<Point> hull;
    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2 && is_cw(hull[hull.size() - 2], hull.back(), p[i])) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }
    for (int i = n - 2, lower_sz = hull.size(); i >= 0; --i) {
        while (hull.size() > lower_sz && is_cw(hull[hull.size() - 2], hull.back(), p[i])) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }
    if (hull.size() > 1) hull.pop_back();
    return hull;
}
