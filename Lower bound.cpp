int findInd(int p) {
    int l = 0,
        r = n;
    while (l<r) {
        int mid = (l+r)/2;
        if (a[mid] < p) l = mid + 1;
        else r = mid;
    }
    return l;
}