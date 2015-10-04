string toString(int a) {
    string res = "";
    if (a == 0) res = "0";
    while (a>0) {
        res = (char)(a % 10 + '0') + res;
        a/=10;
    }
    return res;
}
string divLongToShort(string a, string b) {
    string res = "";
    int val = atoi(b.c_str()), x = 0, k = 0;
    for (int i = 0; i<a.length(); i++) {
        int g = (a[i] - '0');
        if (g == 0 && x == 0) { res += "0"; continue; }
        x = x * 10 + g;
        if (x < val && k == 0 && i<a.length()-1) continue;
        k = 1;
        res += toString(x/val);
        x %= val;
    }

    while (res[0] == '0' && res.length()>1) res.erase(0,1);
    return res;
}
