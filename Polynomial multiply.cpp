/**
	There are some rules to follow about the given input
	A polynomial MUST NOT have spaces, parantheses or any other and other
	character except x, 0..9, +, -, ^
	A polynomial MUST BE correct mathematically
	Let E = +ax^b || -ax^b || +x || -x || +a || -a
	Then a Polynomial P would be
	P = E1E2E2...En
	The main function is PolynomialMultiply::multiply(P1, P2)
	Evaluator is just a helper class
*/

class PolynomialMultiply {
private:
    class Evaluator {
        private :
            static bool okSpace(char c) {
                string ops = "+-/*()";
                return (ops.find(c) != -1);
            }

            static bool isOp(char c) {
                string ops = "+-/*";
                return (ops.find(c) != -1);
            }

            static long double toString(string s, int *error) {
                char *endptr;
                long double val = strtod(s.c_str(), &endptr);
                if (*endptr || s[0] == '.' || s[s.length()-1] == '.') {
                    *error = 1;
                    return 0;
                }
                return val;
            }

            static string tb(string s, int *error) {
                stack<int> ps;
                int brs[201];
                for (int i = 0; i<s.length();i++) {
                    char a = s[i];
                    if (a=='(') ps.push(i+1);
                    else if (a==')') {
                        if (ps.size()==0) {
                            *error = 1;
                            return "0";
                        } else {
                            brs[i] = ps.top();
                            ps.pop();
                        }
                    }
                }
                if (ps.size() != 0) {
                    *error = 1;
                    return "0";
                }
                if (s.length()>1 && brs[s.length()-1] == 1) {
                    return tb(s.substr(1,s.length()-2), error);
                }
                return s;
            }

            static string ws(string s, int *error) {
                while (s.length()>1 && s.find("  ") != -1) {
                    s.erase(s.find("  "),2);
                }
                while (s.find(" ") != -1) {
                    int i = s.find(" ");
                    if (i>0 && i<s.length()-1) {
                        if (!okSpace(s[i-1]) && !okSpace(s[i+1])) {
                            *error = 1;
                            return "0";
                        }
                    }
                    s.erase(i, 1);
                }
                return s;
            }

            static string ab(string s) {
            int i = 0;
            while (i<s.length()) {
                if (i<s.length()-1 && isOp(s[i]) && isOp(s[i+1])) {
                    string f = s.substr(0,i+1);
                    return f + "(" + ab(s.substr(i+1,s.length()-i-1)) + ")";
                }
                i++;
            }
            return s;
        }

            static long double eval(string s, int* error) {
                int len = s.length();
                s = ws(s, error);

                s = tb(s, error);

                s = ab(s);

                if (s.length()==0) {
                    if (s.length()!=len) {
                        *error = 1;
                    }
                    return 0;
                }
                if (*error == 1) {
                    return 0;
                }
                stack<int> ps;
                int brs[201];
                for (int i = 0; i<s.length();i++) {
                    char a = s[i];
                    if (a=='(') ps.push(1);
                    else if (a==')') {
                        if (ps.size()==0) {
                            *error = 1;
                            return 0;
                        } else ps.pop();
                    }
                    brs[i] = ps.size();
                }
                if (ps.size() != 0) {
                    *error = 1;
                    return 0;
                }

                int pl = s.rfind("+"),
                    mn = s.rfind("-"),
                    mp = s.rfind("*"),
                    dv = s.rfind("/"),
                    sn = s.find("sin("),
                    cs = s.find("cos(");
                if (pl != -1) {
                    int p = s.length()-1;
                    while (s.rfind("+",p)!=-1) {
                        int i = s.rfind("+",p);
                        if (brs[i] == 0) {
                            string  s1 = s.substr(0,i),
                                    s2 = s.substr(i+1,s.length()-i-1);
                            if (s2.length() == 0) {
                                *error = 1;
                                return 0;
                            }
                            long double val1 = eval(s1, error);
                            long double val2 = eval(s2, error);
                            return val1+val2;
                        }
                        p = i-1;
                        if(p<0) break;
                    }
                }
                if (mn != -1) {
                    int p = s.length()-1;
                    while (s.rfind("-",p)!=-1) {
                        int i = s.rfind("-",p);
                        if (brs[i] == 0) {
                            string  s1 = s.substr(0,i),
                                    s2 = s.substr(i+1,s.length()-i-1);
                            if (s2.length() == 0) {
                                *error = 1;
                                return 0;
                            }
                            long double val1 = eval(s1, error);
                            long double val2 = eval(s2, error);
                            return val1-val2;
                        }
                        p = i-1;
                        if(p<0) break;
                    }
                }
                if (mp != -1) {
                    int p = s.length()-1;
                    while (s.rfind("*",p)!=-1) {
                        int i = s.rfind("*",p);
                        if (brs[i] == 0) {
                            string s1 = s.substr(0,i),
                            s2 = s.substr(i+1,s.length()-i-1);
                            if (s1.length() == 0 || s2.length() == 0) {
                                *error = 1;
                                return 0;
                            }
                            long double val1 = eval(s1, error);
                            long double val2 = eval(s2, error);
                            return val1*val2;
                        }
                        p = i-1;
                        if(p<0) break;
                    }
                }
                if (dv != -1) {
                    int p = s.length()-1;
                    while (s.rfind("/",p)!=-1) {
                        int i = s.rfind("/",p);
                        if (brs[i] == 0) {
                            string s1 = s.substr(0,i),
                                   s2 = s.substr(i+1,s.length()-i-1);
                            if (s1.length() == 0 || s2.length() == 0) {
                                *error = 1;
                                return 0;
                            }
                            long double val1 = eval(s1, error);
                            long double val2 = eval(s2, error);
                            if (val2 == 0) {
                                    *error = 1;
                                    return 0;
                            }
                            return val1/val2;
                        }
                        p = i-1;
                        if(p<0) break;
                    }
                }
                if (cs != -1) {
                    if (cs == 0 && brs[0] == 0) {
                        string s1 = s.substr(4,s.length()-5);

                        if (s[s.length()-1] != ')') {
                            *error = 1;
                            return 0;
                        }

                        if (s1.length()==0) {
                            *error = 1;
                            return 0;
                        }
                        long double val = cos(eval(s1, error));
                        return val;
                    }
                }
                if (sn != -1) {
                    if (sn == 0 && brs[0] == 0) {
                        string s1 = s.substr(4,s.length()-5);

                        if (s[s.length()-1] != ')') {
                            *error = 1;
                            return 0;
                        }
                        if (s1.length()==0) {
                            *error = 1;
                            return 0;
                        }
                        long double val = sin(eval(s1, error));
                        return val;
                    }

                }
                return toString(s,error);
            }

        public:
            Evaluator();
            static long double evaluate(string s, int *error) {
                *error = 0;
                long double res = eval(s, error);
                return res;
            }

        };
    struct element {
        int coef, power, sign;
    };

    static bool in(string s, int pos) {
        return (pos >= 0 && pos < s.length());
    }
    static bool num(char c) {
        return (c >= '0' && c <= '9');
    }

    static string toString(int n) {
        string s = "";
        n = abs(n);
        while (n > 0) {
            s = (char)(n%10 + '0') + s;
            n/=10;
        }
        return s;
    }
    static vector <element> tokenize(string s) {
        vector <element> tokens;
        if (s[0] != '+' && s[0] != '-') s = "+" + s;
        while (s.find("x") != -1) {
            int x = s.find("x");
            int power = x, coef = x, sign;
            element t = {1, 1, 1};
            if (in(s, power+1) && s[power+1] == '^') {
                power+=2;
                string p = "";
                while (in(s, power) && num(s[power]))  p += s[power++];
                if (!in(s, power) || !num(s[power])) power--;
                t.power = atoi(p.c_str());
            }
            if (in(s, coef-1) && num(s[coef-1])) {
                coef--;
                string p = "";
                while (in(s, coef) && num(s[coef])) p = s[coef--] + p;
                if (!in(s, coef) || !num(s[coef])) coef++;
                t.coef = atoi(p.c_str());
            }
            sign = coef-1;
            if (in(s, sign) && s[sign] == '-') t.sign = -1;

            tokens.push_back(t);
            s.erase(sign, power-sign+1);
        }
        if (s.length() > 0) {
            element t = {1, 0, 1};
            int err = 0;
            double d = Evaluator::evaluate(s, &err);
            d = (int)(round(d));
            t.coef = fabs(d);
            if (d < 0 ) t.sign = -1;
            tokens.push_back(t);
        }
        return tokens;
    }
public:
    static string multiply(string a, string b) {
        vector <element> f = tokenize(a),
                         s = tokenize(b);
        map <int, int> powersCoef;
        for (element n : f) {
            for (element m : s) {
                powersCoef[n.power + m.power] += n.coef * m.coef * n.sign * m.sign;
            }
        }
        string result = "";
        for (auto res : powersCoef) {
            string temp;
            if (res.S == 0) continue;
            if (res.F == 0) {
                if (res.S < 0) temp += "-";
                else temp += "+";
                if (res.S != 0) {
                    string coef = toString(res.S);
                    temp += coef;
                }
            } else {
                if (res.S < 0) temp += "-";
                else temp += "+";
                string coef = toString(res.S);
                if (res.S != 0 && abs(res.S) > 1) temp += coef;
                temp += "x";
                if (res.F > 1) {
                    temp += "^";
                    temp += toString(res.F);
                }
            }
            result = temp + result;
        }
        if (result.length() == 0) result = "0";
        if (result[0] == '+') result.erase(0, 1);
        return result;
    }
};





