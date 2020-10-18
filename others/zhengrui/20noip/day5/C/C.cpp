/*
	Problem:	C.cpp
	Time:		2020-10-17 21:12
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

using namespace std;
const int maxn = 400 + 5, MOD = 1e9 + 7;

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

int n, a[maxn], b[maxn], posa[maxn], posb[maxn];
int s[maxn][maxn];
int up[maxn][maxn];
int f[maxn][maxn][maxn], g[maxn][maxn][maxn], h[maxn][maxn][maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 0, n)
	{
		up[i][0] = 1;
		REP(j, 1, n)
			up[i][j] = 1ll * up[i][j - 1] * (i + j - 1) % MOD;
	}
	REP(i, 1, n) posa[a[i] = read<int>()] = i;
	REP(i, 1, n) posb[b[i] = read<int>()] = i;
	REP(i, 1, n) s[i][0] = s[0][i] = i;
	static int t[maxn];
	REP(i, 1, n)
	{
		REP(j, 1, n) t[j] = 0;
		REP(j, 1, i) t[a[j]]++;
		REP(j, 1, n)
		{
			t[b[j]]++;
			s[i][j] = s[i][j - 1] + (t[b[j]] == 1);
		}
	}
	f[0][0][0] = 1;
	REP(j, 0, n) REP(k, 0, n) REP(i, 0, n / 3)
	{
		if (i && j && k && s[j][k] == s[j - 1][k - 1] + 2) f[i][j][k] = h[i - 1][j - 1][k - 1];

		if (j) g[i][j][k] = g[i][j - 1][k];
		if (!j || s[j][k] == s[j - 1][k]) g[i][j][k] = (g[i][j][k] + f[i][j][k]) % MOD;
		else g[i][j][k] = (1ll * g[i][j][k] * max(0, 3 * i - s[j][k] + 1) + f[i][j][k]) % MOD;

		if (k) h[i][j][k] = h[i][j][k - 1];
		if (!k || s[j][k] == s[j][k - 1]) h[i][j][k] = (h[i][j][k] + g[i][j][k]) % MOD;
		else h[i][j][k] = (1ll * h[i][j][k] * max(0, 3 * i - s[j][k] + 1) + g[i][j][k]) % MOD;
	}
	int ans = h[n / 3][n][n];
	REP(i, 0, n / 3 - 1) ans = 1ll * ans * (3 * i + 1) % MOD * (3 * i + 2) % MOD;
	cout << ans << endl;
	return 0;
}
