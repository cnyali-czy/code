/*
	Problem:	E.cpp
	Time:		2021-05-26 19:49
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
const int maxn = 2000 + 10, MOD = 1e9 + 7;

inline void reduce(int &x) {x += x >> 31 & MOD;}

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

int n, m, k, f[maxn + maxn][maxn][2];
// [Lenth][Sum][Last == 0]

int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	f[0][0][1] = 1;
	REP(l, 0, n + m)
	{
		static int t[maxn];
		REP(s, 0, m)
		{
			int fk = (f[l][s][0] + f[l][s][1]) % MOD;
			reduce(f[l + 1][s][1] += fk - MOD);
			reduce(t[s + 1] += fk - MOD);
			reduce(t[s + min(k - 1, m - s) + 1] -= fk);
//			REP(v, 0, min(k - 1, m - s)) reduce(f[l + 1][s + v][!v] += fk - MOD);
		}
		REP(i, 1, m) reduce(t[i] += t[i - 1] - MOD);
		REP(i, 0, m) reduce(f[l + 1][i][0] += t[i] - MOD), t[i] = 0;
	}
	i64 ans = 0;
	REP(l, 1, n + m) REP(s, 0, m)
		if (s % (k - 1) == m % (k - 1) && l * (k - 1) - s <= n - 1 && (l * (k - 1) - s) % (k - 1) == (n - 1) % (k - 1)) 
			ans += f[l][s][0];
	cout << ans % MOD << endl;
	return 0;
}
