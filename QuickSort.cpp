void qsort(int left, int right, int arr[]) {
    if (left >= right) return;
    int mid = (left + right)/2,
        l = left, r = right;
    do {
        while (arr[l]<arr[mid]) l++;
        while (arr[r]>arr[mid]) r--;

        if (l<=r) {
            int k = arr[l];
            arr[l] = arr[r];
            arr[r] = k;
            l++;
            r--;
        }
    } while (l<r);
    if (left<r) qsort(left, r, arr);
    if (l<right) qsort(l, right, arr);
}