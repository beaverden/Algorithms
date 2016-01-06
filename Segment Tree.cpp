const int maxN = 3*1e5;
int ar[maxN],n;
struct min_segment_tree {
    int t[maxN], n;
    void build(int a[], int m) {
        this->n = m;
        for (int i = n; i<2*n; i++) t[i] = a[i-n];
        for (int i = n-1; i>0; i--) t[i] = min(t[i<<1], t[i<<1|1]);
    }
    int query(int l, int r) {
        int m = inf;
        for ( l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) {
                m = min(m,t[l]);
                l++;
            }
            if (r&1) {
                r--;
                m = min(m,t[r]);
            }
        }
        return m;
    }
} tree;