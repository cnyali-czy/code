#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50 + 5, MOD = 998244353;

int n, m, k, q, a[maxn][maxn], b[maxn][maxn];

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

namespace Gauss
{
	int work()
	{     
		int iter = 0;
		long long res(1);
		REP(i, 1, n)
		{
			if (!a[i][i])
				REP(j, i + 1, n)
					if (a[j][i])
					{
						swap(a[i], a[j]);
						iter++;
						break;
					}
			const int I = inv(a[i][i]);
			REP(j, i + 1, n)
			{
				int tmp = -1ll * a[j][i] * I % MOD;
				REP(k, 1, n)
					(a[j][k] += (1ll * a[i][k] * tmp % MOD)) %= MOD;
			}  
		}
		REP(i, 1, n) (res *= a[i][i]) %= MOD;
		return (iter & 1 ? -res : res);
	} 

}

int main()
{
#ifdef CraZYali
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	while (m--)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		b[x][y] = z;
	}
	while (q--)
	{
		scanf("%d", &k);
		REP(i, 1, n)
			REP(j, 1, n) a[i][j] = b[i][j];
		while (k--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			a[x][y] = 0;
		}
		printf("%d\n", (Gauss::work() + MOD) % MOD);
	}
	return 0;
}
