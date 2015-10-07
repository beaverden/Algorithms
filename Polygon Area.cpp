double ccw(double ax, double ay, double bx, double by, double cx, double cy) {
    return ((bx-ax)*(cy-ay)-(by-ay)*(cx-ax))/2.0;
}

double polygonArea(vector< pair <double, double> > v) {
    double res = 0;
    for (int i = 1;i<v.size()-1; i++)
        res+=ccw(v[0].F,v[0].S,v[i].F,v[i].S,v[i+1].F,v[i+1].S);
    return res;
}