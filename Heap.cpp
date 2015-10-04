struct hheap {
    unsigned int a[125003];
    int n = 0;
    bool comp(int a, int b) {
        if (a%10 >= b%10) return true;
        return false;
    }
    int size() {
        return n;
    }
    void add(unsigned int j) {
        a[++n] = j;
        swim(n);
    }
    void swim(int i) {
        while (i>1 && comp(a[i],a[i/2])) {
            swap(a[i],a[i/2]);
            i/=2;
        }
    }
    void sink(int i) {
        while (2*i <= n) {
            int j = 2*i;
            if (j<n && !comp(a[j],a[j+1])) j++;
            if (comp(a[i],a[j])) break;
            swap(a[i],a[j]);
            i = j;
        }
    }
    unsigned int maxV() {
        return a[1];
    }
    void pop() {
        int t = a[1];
        swap(a[1],a[n--]);
        sink(1);
    }
} heap;