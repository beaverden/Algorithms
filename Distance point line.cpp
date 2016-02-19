double dist(int x1,int y1, int x2, int y2) {
    return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

double ccw(int x1,int y1,int x2,int y2,int x3,int y3) {
    return abs(x1*y2+y1*x3+x2*y3-y2*x3-y3*x1-y1*x2);
}
double distToLine(int mx, int my, int x1, int y1, int x2, int y2) {
    return ccw(mx,my,x1,y1,x2,y2)/dist(x1,y1,x2,y2);
}
