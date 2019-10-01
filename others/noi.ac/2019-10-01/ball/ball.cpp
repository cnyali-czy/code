#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <tr1/unordered_map>
#include <cstdio>

using namespace std;

int n, q, MOD;

int power_pow(long long base, int b, const int MOD = ::MOD)
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
	const int maxn = 120 + 5;
	int M[maxn][maxn + 1];
	int n;

	int x[maxn];

	string s;
	tr1::unordered_map <string, int> id;
	int cur;

	inline void init()
	{
		n = 1;
		REP(i, 1, ::n) n *= i;
		s = "";
		REP(i, 1, ::n) s += (char)i + '0';
		const int keng = ::n * (::n - 1) / 2;
		do
		{
			id[s] = ++cur;
			M[cur][cur] = M[cur][n+1] = keng;
		}while(next_permutation(s.begin(), s.end()));
		s = "";
		REP(i, 1, ::n) s += (char)i + '0';
		do
			REP(i, 0, ::n - 1)
				REP(j, i+1, ::n - 1)
				{
					string qaq = s;
					swap(qaq[i], qaq[j]);
					M[id[s]][id[qaq]] = -1;
				}
		while(next_permutation(s.begin(), s.end()));
		REP(i, 2, n + 1) M[1][i] = 0;
		M[1][1] = 1;
	}

	void work(const int MOD = ::MOD)
	{
		init();
		REP(i, 1, n - 1)
			REP(j, i + 1, n)
			{
				const int Inv = inv(M[i][i]);
				REP(k, i + 1, n + 1)
					(M[j][k] -= 1ll * M[j][i] * Inv % MOD * M[i][k] % MOD) %= MOD;
				M[j][i] = 0;
			}

		DREP(i, n, 1)
		{
			REP(j, i + 1, n)
				(M[i][n + 1] -= 1ll * x[j] * M[i][j] % MOD) %= MOD;
			x[i] = 1ll * M[i][n + 1] * inv(M[i][i]) % MOD;
		}
	}
}
signed main()
{
#ifdef CraZYali
	freopen("ball.in", "r", stdin);
	freopen("ball.out", "w", stdout);
#endif
	cin >> n >> q >> MOD;
	if (n <= 5)
	{
		Gauss::work();
		while (q--)
		{
			string s = "";
			REP(i, 1, n)
			{
				int x;
				scanf("%d", &x);
				s += (char)x + '0';
			}
			printf("%d\n", (MOD + Gauss::x[Gauss::id[s]]) % MOD);
		}
	}
	return 0;
}
