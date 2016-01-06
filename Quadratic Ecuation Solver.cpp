#define pdd pair<double, double>
#define inf 2000000000 //A NUMBER NOT REACHABLE BY ECUATION SOLUTIONS
pdd quadraticSolve(double a, double b, double c) {
    double delta = b*b - 4*a*c;
    if (a == 0) {
        if (b == 0) {
            if (c == 0) return {-inf, -inf};
            return {inf, inf};
        }
        return {-c/b, inf};
    } else {
        if (b == 0) {
            if (!(c > 0 ^ a > 0)) return {inf, inf};
            return {sqrt(-c/a), -sqrt(-c/a)};
        } else {
            if (c == 0) return {0, -b/a};
            if (delta == 0) return {-b/(2*a), inf} ;
            else if (delta < 0) return {inf, inf};
            else return {(-b + sqrt(delta))/(2*a),
                         (-b - sqrt(delta))/(2*a)};
        }
    }
}
