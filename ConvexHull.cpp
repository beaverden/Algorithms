double ccw(double ax, double ay, double bx, double by, double cx, double cy) {
    return ((bx-ax)*(cy-ay)-(by-ay)*(cx-ax))/2.0;
}
vector < pair<double, double> > convexHull(vector < pair<double, double> > v) {
    int lI = 0, n = v.size();
    for (int i = 0; i<n; i++) {
        if (v[i].S < v[lI].S) {
            lI = i;
        } else if (v[i].S == v[lI].S && v[i].F < v[lI].F) {
            lI = i;
        }
    }
    int start = lI, curr = lI;
    vector<pair <double, double> > points;
    do {
        points.push_back({v[curr].F, v[curr].S});
        int next = (curr+1)%n;
        for (int i = 0; i<n; i++) {
            if (ccw(v[curr].F, v[curr].S,v[next].F, v[next].S,v[i].F, v[i].S) < 0) {
                        next = i;
            }
        }
        curr = next;
    } while (curr != start);

    return points;
}