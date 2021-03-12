/*
	Problem:	B.cpp
	Time:		2021-03-08 15:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10, MOD = 1e9 + 7;

int bg[maxn], ne[maxn], to[maxn], w1[maxn], w2[maxn], e;
inline void add(int x, int y, int z1, int z2)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w1[e] = z1;w2[e] = z2;
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)


int n, v, d[maxn];

int f[maxn][6];
void dfs(int x)
{
	f[x][0] = f[x][4] = f[x][5] = 1;
	f[x][1] = d[x];
	f[x][3] = v;
	for (int i = bg[x]; i; i = ne[i])
	{
		int y = to[i];dfs(y);
		static i64 g[6];memset(g, 0, sizeof g);
		i64 c1 = -1ll * w1[i] * w2[i] % MOD, c2 = -w1[i], c3 = -w2[i];
		g[0] = 1ll * f[x][0] * f[y][1] % MOD;
		g[1] = (1ll * f[x][1] * f[y][1] + 1ll * f[x][0] * f[y][0] % MOD * c1) % MOD;
		g[2] = (1ll * f[x][0] * f[y][3] + 1ll * f[x][2] * f[y][1]) % MOD;
		g[3] = (1ll * f[x][1] * f[y][3] + 1ll * f[x][3] * f[y][1] + (1ll * f[x][0] * f[y][2] + 1ll * f[x][2] * f[y][0]) % MOD * c1 + (1ll * f[x][4] * f[y][5] % MOD * c2 + 1ll * f[x][5] * f[y][4] % MOD * c3) % MOD * v) % MOD;
		g[4] = (1ll * f[x][4] * f[y][1] + 1ll * f[x][0] * f[y][4] % MOD * c3) % MOD;
		g[5] = (1ll * f[x][5] * f[y][1] + 1ll * f[x][0] * f[y][5] % MOD * c2) % MOD;
		REP(i, 0, 5) f[x][i] = g[i];
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> v;
	REP(i, 1, n) d[i] = (read<int>() - v + MOD) % MOD;
	REP(i, 2, n)
	{
		int p = read<int>(), b = read<int>(), c = read<int>();
		add(p, i, (b - v + MOD) % MOD, (c - v + MOD) % MOD);
	}
	dfs(1);
	i64 ans = f[1][1] + f[1][3];
	cout << (ans % MOD + MOD) % MOD << endl;
	return 0;
}
