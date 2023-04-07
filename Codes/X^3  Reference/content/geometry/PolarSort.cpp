int quad(point x) {
    if (x.imag() >= 0 && x.real() > 0) return 0;
    if (x.imag() > 0 && x.real() <= 0) return 1;
    if (x.imag() <= 0 && x.real() < 0) return 2;
    return 3;
}
vector <point> angular_sort(vector <point> &v) {
    sort(all(v), [&](point &a, point &b) {
        if (quad(a) != quad(b)) return quad(a) < quad(b);
        return cross(a, b) > 0;
    });
    return v;
}