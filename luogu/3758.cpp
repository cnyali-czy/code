/*
    Problem:    3758.cpp
    Time:       2020-03304 11:10
    Author:     CraZYali
    E-Mail:     yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <ctime>
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 30 + 5, maxk = 1e4 + 10, MOD = 2017;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, lk, M[maxn][maxn];
char s[maxk];

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

namespace GET_DET
{
	int a[maxn][maxn];
	int det(int labda)
	{
		REP(i, 1, n)
		{
			REP(j, 1, n) a[i][j] = M[i][j];
			a[i][i] -= labda;if (a[i][i] < 0) a[i][i] += MOD;
		}
		int ans = 1;
		REP(i, 1, n)
		{
			if (!a[i][i])
				REP(j, i + 1, n) if (a[j][i])
				{
					swap(a[i], a[j]);
					ans = MOD - ans;
					break;
				}
			if (!a[i][i]) return 0;
			(ans *= a[i][i]) %= MOD;
			REP(j, i + 1, n) if (a[j][i])
			{
				int tmp = a[j][i] * inv(a[i][i]) % MOD;
				REP(k, i, n) (a[j][k] -= a[i][k] * tmp % MOD) %= MOD;
			}
		}
		return ans;
	}
}
using GET_DET::det;

int g[maxn << 1];
namespace Gauss
{
	int a[maxn][maxn];
	void init()
	{
		REP(i, 0, n)
		{
			a[i][0] = 1;
			REP(j, 1, n) a[i][j] = a[i][j-1] * i % MOD;
			a[i][n + 1] = det(i);
		}
	}
	void solve()
	{
		REP(i, 0, n)
		{
			if (!a[i][i])
				REP(j, i + 1, n) if (a[j][i])
				{
					swap(a[i], a[j]);
					break;
				}
			REP(j, i + 1, n) if (a[j][i])
			{
				int tmp = a[j][i] * inv(a[i][i]) % MOD;
				REP(k, i, n + 1) (a[j][k] -= a[i][k] * tmp % MOD) %= MOD;
			}
		}
		DEP(i, n, 0)
		{
			REP(j, i + 1, n) (a[i][n + 1] -= a[i][j] * g[j] % MOD) %= MOD;
			g[i] = a[i][n + 1] * inv(a[i][i]) % MOD;
		}
	}
}

int tmp[maxn << 1], ans[maxn << 1], base[maxn << 1], ig[maxn];

int I[maxn][maxn], res[maxn][maxn], Mtmp[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("3758");
#endif
	n = read<int>() + 1;
	REP(Case, 1, read<int>())
	{
		int u(read<int>()), v(read<int>());
		M[u][v] = M[v][u] = 1;
	}
	REP(i, 1, n) M[i][n] = M[i][i] = 1;
	Gauss::init();Gauss::solve();
	REP(i, 0, n) ig[i] = inv(g[i]);
	ans[0] = 1;
	base[1] = 1;
	int t = read<int>();
	while (t)
	{
		if (t & 1)
		{
			//ans *= base
			REP(i, 0, n + n) tmp[i] = 0;
			REP(i, 0, n) if (ans[i])
				REP(j, 0, n) (tmp[i + j] += ans[i] * base[j] % MOD) %= MOD;
			REP(i, 0, n + n) ans[i] = tmp[i];
			//ans %= MOD
			DEP(i, n + n, n) if (ans[i])
			{
				int tmp = ans[i] * ig[n] % MOD;
				REP(j, 0, n) (ans[i - j] -= tmp * g[n - j] % MOD) %= MOD;
			}
		}
		//base *= base
		REP(i, 0, n + n) tmp[i] = 0;
		REP(i, 0, n) if (base[i])
			REP(j, 0, n) (tmp[i + j] += base[i] * base[j] % MOD) %= MOD;
		REP(i, 0, n + n) base[i] = tmp[i];
		//base %= MOD
		DEP(i, n + n, n) if (base[i])
		{
			int tmp = base[i] * ig[n] % MOD;
			REP(j, 0, n) (base[i - j] -= tmp * g[n - j] % MOD) %= MOD;
		}
		t >>= 1;
		//      REP(i, 0, n + n) printf("%d%c", base[i], i == end_i ? '\n' : ' ' );
	}
	REP(i, 1, n) I[i][i] = 1;
	REP(qaq, 0, n)
	{
		if (ans[qaq]) REP(i, 1, n) REP(j, 1, n) (res[i][j] += ans[qaq] * I[i][j] % MOD) %= MOD;
		REP(i, 1, n) REP(j, 1, n) Mtmp[i][j] = 0;
		REP(i, 1, n)
			REP(k, 1, n) if (I[i][k])
			REP(j, 1, n) (Mtmp[i][j] += I[i][k] * M[k][j] % MOD) %= MOD;
		REP(i, 1, n) REP(j, 1, n) I[i][j] = Mtmp[i][j];
	}
	long long ans = 0;
	REP(i, 1, n) ans += res[1][i];
	cout << (ans % MOD + MOD) % MOD << endl;
	return 0;
}
