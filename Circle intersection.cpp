const double pi = 3.14159265358979323846;

double dist(int x1,int y1,int x2,int y2) {
    return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}
/*
A - center of the first circle
B - center of the second circle
C, D - intersection points
*/

double cirlceIntersectionArea(double x1,double y1,double x2,double y2,double r1, double r2) {
    if (x1 == x2 && y1 == y2) return pi*r1*r1;
    double c = dist(x1,y1,x2,y2);
    if (c > r1+r2) return 0;
    double CBA = acos( ( r2*r2 + c*c - r1*r1 )/(2*r2*c) );
    double CBD = 2*CBA;

    double CAB = acos( ( r1*r1 + c*c - r2*r1 )/(2*r1*c) );
    double CAD = 2*CAB;

    double Area = (0.5)*(CBD)*r2*r2 - (0.5)*r2*r2*sin(CBD)
                + (0.5)*(CAD)*r1*r1 - (0.5)*r1*r1*sin(CAD);
    return Area;

}
