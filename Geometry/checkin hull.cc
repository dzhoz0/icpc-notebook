bool checkin_hull(Point k, const std::vector<Point> &hull) {
    if (hull.size() == 2) {
        if (is_collinear(k, hull[0], hull[1])) {
            return (k.x >= std::min(hull[0].x, hull[1].x) && k.x <= std::max(hull[0].x, hull[1].x) && 
                    k.y >= std::min(hull[0].y, hull[1].y) && k.y <= std::max(hull[0].y, hull[1].y));
        }
        return false;
    }

    int l = 2, r = hull.size() - 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        // is_cw here returns <= 0
        if (is_cw(hull[0], hull[mid], k)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (ans == -1) return false;

    return (area_triangle(hull[0], hull[ans], hull[ans - 1]) ==
    area_triangle(hull[0], hull[ans - 1], k) +
    area_triangle(hull[ans - 1], hull[ans], k) +
    area_triangle(hull[ans], hull[0], k));
}
