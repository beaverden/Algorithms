/***
A library that does some operations with BigIntegers like addition 
(non-negative), substraction, multiplying, dividing, taking modulus, gcd and lcm;
***/

class BigInt {
    private:
        string number;
        //Helper functions
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
        void setVal(string s){
            number = s;
        }
        string toString(int a) {
            string res = "";
            if (a == 0) res = "0";
            while (a>0) {
                res = (char)(a % 10 + '0') + res;
                a/=10;
            }
            return res;
        }

        inline bool operator==(BigInt& lhs){ return (this->val()==lhs.val());}
        inline bool operator!=(BigInt& lhs){return !(lhs==*this); }
        inline bool operator<(BigInt& lhs){
            if (this->length()<lhs.length()) return true;
            else if (this->length()>lhs.length()) return false;
            else if (this->val()<lhs.val()) return true;
            return false;
        }
        inline bool operator>(BigInt& lhs){return lhs<*this; }
        inline bool operator<=(BigInt& lhs){return !(*this>lhs); }
        inline bool operator>=(BigInt& lhs){return !(*this<lhs); }
        BigInt& operator=(BigInt that) {
            this->setVal(that.val());
            return *this;
        }
        //Works only for positive integers
        BigInt& operator+=(BigInt& that) {
            string a = this->number, b = that.number;
            while (a.length() < b.length()) a = "0" + a;
            while (b.length() < a.length()) b = "0" + b;
            string c;
            int r = 0, t;
            for(int i = 0; i<a.length(); i++) {
                int x = (a[a.length()-i-1] - '0'),
                    y = (b[a.length()-i-1] - '0');
                t = x+y+r;
                c += (char)( (t % 10) + '0');
                r = t/10;
            }
            if (r != 0) c += (char)( r + '0');
            reverse(c.begin(), c.end());
            this->setVal(c);
            return *this;
        }
        BigInt& operator+=(int that) {
            BigInt t(that);
            *this += t;
            return *this;
        }
        BigInt operator+(BigInt& that) {
            BigInt cp = *this;
            cp += that;
            return cp;
        }
        BigInt& operator++(){
            *this += 1;
            return *this;
        }
        BigInt& operator-=(BigInt& that) {
            string a = this->val(), b = that.val();
            while (a.length() < b.length()) a = "0" + a;
            while (b.length() < a.length()) b = "0" + b;
            int borrow = 0, neg = 0;
            if (a<b) { swap(a,b); neg = 1; }
            string res;
            for (int i = 0; i < a.length(); i++) {
                int x = a[a.length()-i-1]-'0',
                    y = b[a.length()-i-1]-'0',
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
            this->setVal(res);
            return *this;
        }
        BigInt& operator-=(int that) {
            BigInt t(that);
            *this -= t;
            return *this;
        }
        BigInt operator-(BigInt& that) {
            BigInt cp = *this;
            cp -= that;
            return cp;
        }
        BigInt& operator--(){
            *this -= 1;
            return *this;
        }
        BigInt& operator*=(BigInt& that) {
            string a = this->val(), b = that.val();
            int res[10000]={0},shift=0;
            if (a.length()<b.length()) swap(a,b);
            int lenA = a.length(),
                lenB = b.length(),
                finlen=0;
            for (int i=0;i<lenB;i++) {
                int rem = 0,z=shift;
                for (int j=0;j<lenA;j++) {
                    int x = b[lenB-i-1]-'0',
                        y = a[lenA-j-1]-'0';
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
            this->setVal(fin);
            return *this;
        }
        BigInt& operator*=(int that) {
            BigInt t(that);
            *this *= t;
            return *this;
        }
        BigInt operator*(BigInt& that) {
            BigInt cp = *this;
            cp *= that;
            return cp;
        }
        BigInt& operator/=(BigInt& that) {
            BigInt one("1");
            if (*this<that) {
                this->setVal("0");
                return *this;
            }
            BigInt l("1"), r = *this, last;
            while (l<=r) {
                BigInt mid = l+r;
                mid = mid/2;
                BigInt t = mid * that;
                if (t <= *this) {
                    last = mid;
                    l = mid + one;
                } else {
                    r = mid - one;
                }
            }
            this->setVal(last.val());
            return *this;
        }
        BigInt& operator/=(int that) {
            string a = this->number;
            string res = "";
            int val = that, x = 0, k = 0;
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
            this->setVal(res);
            return *this;
        }
        BigInt operator/(BigInt that) {
            BigInt cp = *this;
            cp /= that;
            return cp;
        }
        BigInt operator/(int that) {
            BigInt cp = *this;
            cp /= that;
            return cp;
        }
        BigInt& operator%=(BigInt& that) {
            BigInt dv = *this/that;
            BigInt prod = dv*that;
            *this -= prod;
            return *this;
        }
        BigInt& operator%=(int that) {
            BigInt t(that);
            *this %= t;
            return *this;
        }
        BigInt operator%(BigInt& that) {
            BigInt cp = *this;
            cp %= that;
            return cp;
        }
        static BigInt gcd(BigInt a, BigInt b) {
            BigInt zero("0");
            while (b>zero) {
                BigInt t = b;
                b = a%b;
                a = t;
            }
            return a;
        }
        static BigInt lcm(BigInt a, BigInt b) {
            return (a*b)/gcd(a,b);
        }
};