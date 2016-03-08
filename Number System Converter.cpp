int getOrd(char c) {
    if (c >= '0' && c <= '9') return c-'0';
    else if (c >= 'A' && c <= 'Z') return 10 + c-'A';
}
char getChar(BigInt n) {
    int t = atoi(n.val().c_str());

    if (t<10) return (char)('0' + t);
    else return (char)('A'+ t-10);
}

BigInt XtoDec(string num, int x) {
    BigInt multiplier(1);
    BigInt result(0);
    int i = num.length()-1;
    while (i>=0) {
        char c = num[i];
        i--;
        BigInt repr(getOrd(c));
        repr = repr.multiply(multiplier);
        result = result.add(repr);
        multiplier = multiplier.multiply(x);
    }
    return result;
}

string DecToY(BigInt num, int y) {
    string res;
    BigInt BigY(y);
    do{
        BigInt rem = num.modulus(BigY);
        num = num.divide(y);
        res = getChar(rem) + res;
    } while (num.compare(0) > 0);
    return res;
}

string fromXtoY(string number, int x, int y) {
    BigInt num = XtoDec(number,x);
    string res = DecToY(num,y);
    return res;
}