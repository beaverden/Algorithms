string longAdd(string a, string b) {
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    while (a.length() < b.length()) a += "0";
    while (b.length() < a.length()) b += "0";
    string c;
    int r = 0, t;
    for(int i = 0; i<a.length(); i++) {
        int x = (a[i] - '0'),
            y = (b[i] - '0');
        t = x+y+r;
        c += (char)( (t % 10) + '0');
        r = t/10;
    }
    if (r != 0) c += (char)( r + '0');
    reverse(c.begin(), c.end());
    return c;
}

