//At the end, prime indicies in the array will be FALSE, and not primes will be TRUE
const int maxN = 1e5 + 1;
bool primes[maxN];

void sieve() {
    int i = 2;
    for (int i = 2; i*i <= maxN; i++) {
        if (!primes[i]) {
            for (int j = i+i; j <= maxN; j += i) primes[j] = true;
        }
    }
}