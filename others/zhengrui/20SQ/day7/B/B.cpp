/*
	Problem:	B.cpp
	Time:		2020-09-19 21:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

#define i64 long long
using namespace std;
const int maxn = 1e4 + 10, maxk = 500 + 5, MOD = 998244353;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, k;

int f[maxn][maxk], g[maxn][maxk], siz[maxn];
void dp(int x, int fa)
{
	siz[x] = 1;
	f[x][0] = 1;
	g[x][1] = 1;
	for (int i = bg[x], y = to[i]; i; y = to[i = ne[i]]) if (y ^ fa)
	{
		dp(y, x);
		static int tmf[maxk], tmg[maxk];
		REP(j, 0, siz[x])
			REP(k, 0, min(siz[y], ::k - j))
			{
				tmf[j + k] = (tmf[j + k] + 1ll * f[x][j] * f[y][k]) % MOD;
				tmg[j + k] = (tmg[j + k] + 1ll * f[x][j] * g[y][k] + 1ll * g[x][j] * f[y][k]) % MOD;
			}
		siz[x] = min(siz[x] + siz[y], ::k);
		REP(k, 0, siz[x])
		{
			f[x][k] = tmf[k];tmf[k] = 0;
			g[x][k] = tmg[k];tmg[k] = 0;
		}
	}
	REP(j, 1, siz[x]) f[x][j] = g[x][j];
	f[x][1]--;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();k = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dp(1, 0);
	i64 ans = 0;
	REP(i, 0, k) ans += f[1][i];
	cout << (MOD + ans % MOD) % MOD << endl;
	return 0;
}
