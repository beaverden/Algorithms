const int maxM = 3*1e5;
int n;
struct interval_tree {
    int t[maxM];
    void build() {
        for (int i = n-1; i>0; i--) t[i] = max(t[i<<1], t[i<<1|1]);
    }
    int query(int l, int r) {
        int m = 0;
        for ( l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) {
                m = max(m,t[l]);
                l++;
            }
            if (r&1) {
                r--;
                m = max(m,t[r]);
            }
        }
        return m;
    }
} tree;