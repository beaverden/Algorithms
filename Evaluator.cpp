/***
	Correctly evaluates expressions involving any <6 byte floating point numbers and
	oppertions "+", "-", "*", "/", "sin", "cos" and brackets
***/

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
        if (*endptr) {
            *error = 1;
            return 0;
        }
        return val;
    }

    static string trimBrackets(string s, int *error) {
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
            return trimBrackets(s.substr(1,s.length()-2), error);
        }
        return s;
    }

    static string eliminateWhiteSpaces(string s, int *error) {
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

    static string addBrackets(string s) {
		int i = 0;
		while (i<s.length()) {
			if (i<s.length()-1 && isOp(s[i]) && isOp(s[i+1])) {
				string f = s.substr(0,i+1);
				return f + "(" + addBrackets(s.substr(i+1,s.length()-i-1)) + ")";
			}
			i++;
		}
		return s;
	}

    static long double eval(string s, int* error) {
        int len = s.length();
        /*** WHITE SPACES DELETING ***/
        s = eliminateWhiteSpaces(s, error);
        /*** WHITE SPACES DELETING ***/

        /*** BRACKET DELETING ***/
        s = trimBrackets(s, error);
        /*** BRACKET DELETING ***/

        /*** ADD BRACKETS BETWEEN OPERATORS ***/
        s = addBrackets(s);
        /*** ADD BRACKETS BETWEEN OPERATORS ***/

        if (s.length()==0) {
            if (s.length()!=len) {
                *error = 1;
            }
            return 0;
        }
        if (*error == 1) {
            return 0;
        }
        /*** CALCULATING THE NUMBER OF PARANTHESIS IN EACH POSITION ***/
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