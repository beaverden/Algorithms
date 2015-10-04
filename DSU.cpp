struct dsu {
    int p[1000],rank[1000];
    void init() {
        for (int i=0;i<1000;i++) {
            p[i]=i;
            rank[i]=1;
        }
    }
    int parent(int v) {
        return (p[v]==v)? v : (p[v]=parent(p[v]));
    }
    void merge(int x, int y) {
        if ((x=parent(x))==(y=parent(y))) return;
        if (rank[y]>rank[x]) swap(x,y);
        rank[x]+=rank[y];
        p[y]=x;
    }
};