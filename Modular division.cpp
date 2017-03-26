
long long inverse(long long a)
{
    a = a%mod;
    for (int x=1; x<mod; x++)
       if ((a*x) % mod == 1)
          return x;
}

long long divide(long long a, long long b) {
    return ((a%mod)*(inverse(b)%mod))%mod;
}