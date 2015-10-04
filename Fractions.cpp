#define pii pair<int, int>
struct frac {

    pii multiply(pii a, pii b) {
        return {a.F * b.F , a.S * b.S};
    }
    pii add(pii a, pii b) {
        return {a.F * b.S + b.F * a.S, b.S * a.S};
    }
    pii subst(pii a, pii b) {
        return {a.F * b.S - b.F * a.S, b.S * a.S};
    }
    pii reduce(pii a) {
        i64 g = __gcd(abs(a.F), abs(a.S));
        return {a.F/g, a.S/g};
    }
    int compare(pii a, pii b) {
        i64 f = a.F * b.S,
            s = b.F * a.S;
        if (f > s) return 1;
        else if (f < s) return -1;
        return 0;
    }

}