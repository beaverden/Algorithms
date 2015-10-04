void build(int n) {
    for (int i=n-1;i>0;--i)
            t[i]=t[i<<1]+t[i<<1|1];
}
void modify(int p, int value) {
    for (t[p+=n]=value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}
__int64 sum(int l,int r) {
    __int64 res = 0;
    l+=n; r+=n;
    for (; l<r; l>>=1, r>>=1) {
        if (l&1) res=res+t[l++];
        if (r&1) res=res+t[--r];
    }
    return res;
}