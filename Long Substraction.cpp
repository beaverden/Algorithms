int comp(string a, string b) {
    if (a.length()>b.length()) return 1;
    else if (b.length()>a.length()) return -1;
    else if (a>b) return 1;
    else if (a<b) return -1;
    return 0;
}
string longSubstract(string a, string b) {
    while (a.length()<b.length()) a='0'+a;
    while (b.length()<a.length()) b='0'+b;
    int borrow = 0, neg = 0;
    if (comp(a,b)<0) { swap(a,b); neg = 1; }
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    string res;
    for (int i = 0; i < a.length(); i++) {
        int x = a[i]-'0',
            y = b[i]-'0',
            z=0;
        if (x-borrow<y) {
            z=(10+x-y-borrow);
            if (borrow == 0) borrow++;
        } else {
            z=x-borrow-y;
            borrow=0;
        }
        res+=(char)(z+'0');
    }
    reverse(res.begin(),res.end());
    while (res[0]=='0' && res.length()>1) res.erase(0,1);
    if (neg>0) res="-"+res;
    return res;
}