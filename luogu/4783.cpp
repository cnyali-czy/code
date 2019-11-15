//test
#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 400 + 10, MOD = 1e9 + 7;

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

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, a[maxn][maxn];
int swapi[maxn], swapj[maxn];

int main()
{
#ifdef CraZYali
	file("4783");
#endif
	n = read<int>();
	REP(i, 1, n)
		REP(j, 1, n) a[i][j] = read<int>();
	REP(k, 1, n)
	{
		int &_i = swapi[k], &_j = swapj[k];
		REP(i, k, n)
			REP(j, k, n) if (a[i][j])
			{
				_i = i;
				_j = j;
				break;
			}
		REP(j, 1, n)
			swap(a[k][j], a[_i][j]);
		REP(i, 1, n)
			swap(a[i][k], a[i][_j]);
		if (!a[k][k])
		{
			puts("No Solution");
			return 0;
		}
		a[k][k] = inv(a[k][k]);
		REP(j, 1, n) if (j ^ k)
			a[k][j] = 1ll * a[k][j] * a[k][k] % MOD;
		REP(i, 1, n) if (i ^ k)
			REP(j, 1, n) if (j ^ k)
			(a[i][j] -= 1ll * a[i][k] * a[k][j] % MOD) %= MOD;
		REP(i, 1, n) if (i ^ k)
			a[i][k] = -1ll * a[i][k] * a[k][k] % MOD;
	}
	DEP(k, n, 1)
	{
		REP(j, 1, n)
			swap(a[k][j], a[swapj[k]][j]);
		REP(i, 1, n)
			swap(a[i][k], a[i][swapi[k]]);
	}
	REP(i, 1, n)
		REP(j, 1, n)
		printf("%d%c", (MOD + a[i][j]) % MOD, j == n ? '\n' : ' ');
	return 0;
}
