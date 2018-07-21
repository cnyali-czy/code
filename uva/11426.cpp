#define REP(i, s, e) for (register int i = s; i <= e ;i++)

#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 4000000 + 10;

int n, m, k;

long long phi[maxn];
inline void gen_phi()
{
    phi[1] = 1;
    REP(i, 2, maxn - 10)
        if (!phi[i])
            for (register int j = i ; j <= maxn - 10 ; j += i)
            {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
}

long long s[maxn], f[maxn];

int main()
{
#ifdef CraZYali
	freopen("11426.in", "r", stdin);
	freopen("11426.out", "w", stdout);
#endif
    gen_phi();
    REP(i, 1, maxn - 10)
        for (register int j = i << 1; j <= maxn - 10; j += i)
            f[j] += i * phi[j / i];
    REP(i, 2, maxn - 10) s[i] = s[i - 1] + f[i];
    while (scanf("%d", &n) * n) printf("%lld\n", s[n]);
    return 0;
}
