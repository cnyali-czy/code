/*
	Problem:	A.cpp
	Time:		2020-07-29 19:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

inline bool chkmax(int &a, int b) {if (a < b) {a = b;return 1;}return 0;}
inline bool chkmin(int &a, int b) {if (a > b) {a = b;return 1;}return 0;}

#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 250 + 5, inf = 1e9;

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

int n, m, a[maxn], ans = inf;
int d[maxn][maxn], f[maxn][maxn], g[maxn][maxn];

struct node
{
	int x, y, z, type;
	node(int x = 0, int y = 0, int z = 0, int type = 0) : x(x), y(y), z(z), type(type) {}
	inline bool operator < (const node &B) const {return z > B.z;}
};
priority_queue <node> q;

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) REP(j, 1, n) d[i][j] = f[i][j] = g[i][j] = inf;
	REP(i, 1, n) a[i] = read<int>(), d[i][i] = a[i];
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		d[x][y] = a[x] + a[y];
	}
	REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) chkmin(d[i][j], d[i][k] + d[k][j] - a[k]);
	REP(i, 2, n)
	{
		f[1][i] = d[i][1];
		q.emplace(1, i, f[1][i], 0);
	}
	while (!q.empty())
	{
		auto u = q.top();q.pop();
		int i = u.x, j = u.y, t = u.type;
		if (!t	&& f[i][j] < u.z) continue;
		if ( t	&& g[i][j] < u.z) continue;
		if (!t	&& j == n)
		{
			chkmin(ans, f[i][n] + d[i][n] - a[i] - a[n]);
			continue;
		}
		if (t == 1)
		{
			REP(k, 2, n) if (k ^ j)
			{
				int res = u.z + d[i][j] + d[k][i] - a[i] - a[i] - a[j];
				if (chkmin(f[j][k], res)) q.emplace(j, k, res, 0);
			}
		}
		else
			REP(k, 2, n)
			{
				int res = u.z + d[i][k] - a[i];
				if (chkmin(g[k][j], res)) q.emplace(k, j, res, 1);
			}
	}
	printf("%d\n", ans < inf ? ans : -1);
	return 0;
}
