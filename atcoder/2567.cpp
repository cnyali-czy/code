/*
	Problem:	2567.cpp
	Time:		2020-11-30 19:01
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 300 + 5, MOD = 1e9 + 7;

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

int n, m, f[maxn][maxn], g[maxn][maxn];
vector <pair <int, int> > v[maxn];
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void revinc(int x, int &y) {inc(y, x);}
int main()
{
#ifdef CraZYali
	file("2567");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int l = read<int>(), r = read<int>(), lim = read<int>();
		v[r].emplace_back(l, lim);
		if (r == 1 && lim != 1)
		{
			puts("0");
			return 0;
		}
	}
	f[0][0] = 1;
	REP(i, 2, n)
	{
		swap(f, g);
		memset(f, 0, sizeof f);
		REP(a, 0, i - 1) REP(b, 0, i - 1)
		{
			revinc(g[a][b], f[a][b]);	
			revinc(g[a][b], f[i - 1][b]);//(i - 1, a, b) -> (i - 1, i, b)
			revinc(g[a][b], f[i - 1][a]);//(i - 1, a, b) -> (i - 1, a, i)
		}
		for (auto j : v[i])
		{
			int l = j.first, lim = j.second;
			REP(A, 0, i) REP(B, 0, i)
			{
				int here = (l <= A) + (l <= B) + 1;
				if (here != lim) f[A][B] = 0;
			}
		}
	}
	i64 ans = 0;
	REP(i, 0, n) REP(j, 0, n) ans += f[i][j];
	cout << ans * 3 % MOD << endl;
	return 0;
}
