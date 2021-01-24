/*
	Problem:	A.cpp
	Time:		2021-01-19 19:52
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1000 + 10;

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

int n, a[maxn], b[maxn], c[maxn], W, D;

void chkmin(int &x, int y) {if (x > y) x = y;}
int dis[maxn][maxn], to[maxn][maxn];

int f[15][maxn][maxn];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>(), b[i] = read<int>(), c[i] = read<int>();
	W = read<int>();D = read<int>();
	REP(i, 1, n) REP(j, i + 1, n) dis[i][j] = dis[j][i] = abs(a[i] - a[j]) + abs(b[i] - b[j]);
	REP(i, 1, n)
	{
		REP(j, 1, n) to[i][j] = j;
		sort(to[i] + 1, to[i] + 1 + n, [&](int x, int y) {return dis[i][x] > dis[i][y];});
	}
	memset(f, 0x3f, sizeof f);int inf = f[0][0][0];
	f[1][0][1] = 0;
	REP(d, 1, D) REP(i, 1, n)
	{
		int res = inf;
		REP(j, 1, n) if (dis[i][j] <= W) chkmin(res, f[d][j][i] + c[i] * dis[i][j]);
		REP(j, 1, n) if (dis[i][j] <= W)
		{
			chkmin(f[d + 1][i][j], min(res, f[d][0][i] + W * c[i]));
			chkmin(f[d + 1][0][j], f[d][0][i] + c[i] * dis[i][j]);
		}
		res = inf;
		for (int k = n, cur = 1; k >= 1; k--)
		{
			int j = to[i][k];
			if (dis[i][j] > W) break;
			while (cur <= n)
			{
				int l = to[i][cur];
				if (W - dis[i][l] > dis[i][j]) break;
				cur++;
				if (dis[i][l] <= W) chkmin(res, f[d][l][i] - c[i] * (W - dis[i][l]));
			}
			chkmin(f[d + 1][0][j], res + dis[i][j] * c[i]);
		}
	}
	if (f[D + 1][0][2] < inf) cout << f[D + 1][0][2] << endl;
	else puts("-1");
	return 0;
}
