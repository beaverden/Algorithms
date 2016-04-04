const int maxV = 50;
i64 a[maxV][maxV];
i64 stirlingNumbers(int n, int k) {
    a[0][0] = 1;
    for (int i = 1; i<=maxV; i++)
        for (int j = 1; j<=maxV; j++) {
            a[i][j] = j*a[i-1][j] + a[i-1][j-1];
        }
    return a[n][k];
}