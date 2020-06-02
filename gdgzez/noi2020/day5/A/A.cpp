#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 100 + 5, inf = 5e8;

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

int m, n, k;
int G[maxn][maxn], f[maxn][1 << 10];

int Min[maxn], vis[maxn];
void work(int S)
{
	REP(i, 0, n - 1) Min[i] = f[i][S];
	REP(i, 0, n - 1) vis[i] = 0;
	while (1)
	{
		int xmn = inf, id = -1;
		REP(i, 0, n - 1) if (!vis[i] && Min[i] < xmn) xmn = Min[id = i];
		if (id == -1) return;
		vis[id] = 1;
		f[id][S] = xmn;
		REP(i, 0, n - 1) chkmin(Min[i], Min[id] + G[id][i]);
	}
}
inline bool check(int x)
{
	for (int i = 0; i < k; i += 2) if ((x >> i & 1) ^ (x >> (i + 1) & 1)) return 0;
	return 1;
}
int w[1 << 10];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 0, n) REP(j, 0, n) G[i][j] = inf;
	REP(i, 1, m)
	{
		int x(read<int>() - 1), y(read<int>() - 1), z(read<int>());
		chkmin(G[x][y], z);
		chkmin(G[y][x], z);
	}
	REP(i, 0, n) G[i][i] = 0;
	REP(k, 0, n - 1) REP(i, 0, n - 1) if (G[i][k] < inf)
		REP(j, 0, n - 1) chkmin(G[i][j], G[i][k] + G[k][j]);
	const int lim = (1 << k) - 1;
	REP(S, 1, lim)
	{
		REP(i, 0, n - 1)
		{
			f[i][S] = inf;
			for (int x = S; x; x = (x - 1) & S)
				chkmin(f[i][S], f[i][x] + f[i][S ^ x]);
		}
		if (S == (S & -S))
			REP(i, 0, k - 1)
			{
				f[i][S] = inf;
				if (S >> i & 1) f[i][S] = 0;
			}
		work(S);
	}
	REP(S, 1, lim)
	{
		w[S] = inf;
		if (check(S))
			REP(i, 0, n - 1) chkmin(w[S], f[i][S]);
	}
	REP(S, 1, lim)
		for (int x = S; x; x = (x - 1) & S) chkmin(w[S], w[S ^ x] + w[x]);
	cout << w[lim] << endl;
	return 0;
}
