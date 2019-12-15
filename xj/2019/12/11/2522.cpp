#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 50000 + 10;

int prime[maxn], notp[maxn], p_cnt;
int mu[maxn], sum[maxn];

struct __init__
{
	__init__(const int n = 50000)
	{
		sum[1] = mu[1] = 1;
		REP(i, 2, n)
		{
			if (!notp[i]) mu[prime[++p_cnt] = i] = -1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > n) break;
				notp[tmp] = 1;
				if (i % prime[j]) mu[tmp] = -mu[i];
				else break;
			}
			sum[i] = sum[i-1] + mu[i];
		}
	}
}__INIT__;
int k;
long long calc(int n, int m)
{
	if (n > m) swap(n, m);
	long long res(0);
	n /= k;m /= k;
	for (int i(1), j; i <= n; i = j + 1)
	{
		j = min(n / (n / i), m / (m / i));
		res += 1ll * (n / i) * (m / i) * (sum[j] - sum[i-1]);
	}
	return res;
}

signed main()
{
#ifdef CraZYali
	freopen("2522.in", "r", stdin);
	freopen("2522.out", "w", stdout);
#endif
	register int T;cin >> T;
	while (T--)
	{
		int a, b, c, d;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		printf("%lld\n", calc(b, d) - calc(a - 1, d) - calc(b, c - 1) + calc(a - 1, c - 1));
	}
	return 0;
}
