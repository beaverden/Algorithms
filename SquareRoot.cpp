double squareRoot(double n) {
    double res = 1;
    int steps = 10000;
    while (steps--) {
        res = (0.5)*(res + n/res);
    }
    return res;
}