for (int i = 0; i < hull.size(); ++i) {
    int k = i + 1;
    for (int j = i + 2; j < hull.size(); ++j) {
        while (k + 1 < j && area_triangle(hull[i], hull[j], hull[k]) <= area_triangle(hull[i], hull[j], hull[k + 1])) {
            ++k;
        } 
        ans = std::max(ans, area_triangle(hull[i], hull[j], hull[k]));
    }
}
ans /= 2;
