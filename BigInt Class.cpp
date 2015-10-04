class BigInt {
    private:
        string number;
        //Helper functions
        string toString(int a) {
            string res = "";
            if (a == 0) res = "0";
            while (a>0) {
                res = (char)(a % 10 + '0') + res;
                a/=10;
            }
            return res;
        }
        int comp(string a, string b) {
            if (a.length()>b.length()) return 1;
            else if (b.length()>a.length()) return -1;
            else if (a>b) return 1;
            else if (a<b) return -1;
            return 0;
        }
    public:

        BigInt(string s) {
            number = s;
        }
        BigInt(int s) {
            number = toString(s);
        }
        BigInt() {
            number = "0";
        }
        void write() {
            cout << number;
        }
        int length() {
            return number.length();
        }
        string val() {
            return number;
        }
        int compare(BigInt that) {
            if (this->length() > that.length()) return 1;
            else if (this->length() < that.length()) return -1;
            else if (this->number > that.number) return 1;
            else if (this->number < that.number) return -1;
            return 0;
        }
        //Works only for positive integers
        BigInt add (BigInt that) {
            string a = number, b = that.number;
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
            return BigInt(c);
        }
        //Works for positive integers
        BigInt divLongToShort(BigInt that) {
            string a = number, b = that.val();
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
            return BigInt(res);
        }
        BigInt longProd(BigInt that) {
            string a = number, b = that.val();
            int res[2500]={0},shift=0;
            reverse(a.begin(),a.end());
            reverse(b.begin(),b.end());
            if (a.length()<b.length()) swap(a,b);
            int lenA = a.length(),
                lenB = b.length(),
                finlen=0;
            for (int i=0;i<lenB;i++) {
                int rem = 0,z=shift;
                for (int j=0;j<lenA;j++) {
                    int x = b[i]-'0',
                        y = a[j]-'0';
                    int prod = x*y+rem+res[z];
                    res[z]=prod%10;
                    rem=prod/10;
                    z++;
                }
                finlen=max(finlen,--z);
                while (rem>0) {
                        int newLen = z++;
                        res[z]+=rem;
                        rem=res[z]/10;
                        res[z]%=10;
                        finlen=max(finlen,z);
                        }
                shift++;
            }
            string fin;
            for (int i=finlen;i>=0;i--) fin+=(char)(res[i]+'0');
            while (fin[0]=='0' && fin.length()>1) fin.erase(0,1);
            return BigInt(fin);
        }
        BigInt longSubstract(BigInt that) {
            string a = number, b = that.val();
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
            return BigInt(res);
        }

};