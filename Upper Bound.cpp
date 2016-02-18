int upper_bound(int val, vector <int> v, int maxSize) {
    int l = 0, 
		r = maxSize;
    while (l<r) {
        int mid = (l+r)/2;
        if (v[mid] > val)  r = mid;
        else l = mid+1;
    }
    return l;
}