#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10, maxm = 5e5 + 10 + maxn, inf = 1e9;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

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

int m, n, k, S, T;
int im[maxn];

int dis[maxn];
priority_queue <pair <int, int> > Q;

int dij()
{
	REP(i, 1, T) dis[i] = inf;
	dis[S] = 0;
	Q.emplace(0, S);
	while (!Q.empty())
	{
		int x = Q.top().second, y = Q.top().first;Q.pop();
		if (y > dis[x]) continue;
		for (int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] > dis[x] + w[i])
			{
				dis[to[i]] = dis[x] + w[i];
				Q.emplace(-dis[to[i]], to[i]);
			}
	}
	return dis[T];
}
int x[maxm], y[maxm], z[maxm];

int main()
{
#ifdef CraZYali
	file("5304");
#endif
	REP(Case, 1, read<int>())
	{
		n = read<int>();m = read<int>();k = read<int>();
		S = n + 1;T = n + 2;
		REP(i, 1, m)
			x[i] = read<int>(), y[i] = read<int>(), z[i] = read<int>();
		REP(i, 1, k) im[i] = read<int>();
		int ans = inf;
		int l = 1, L = 0;
		while (l <= n) l <<= 1, L++;
		REP(p, 0, L)
		{
			REP(i, 1, T) bg[i] = 0;e = 0;
			REP(i, 1, m) add(x[i], y[i], z[i]);
			REP(i, 1, k)
				if (im[i] >> p & 1)	add(S, im[i], 0);
				else				add(im[i], T, 0);
			int res = dij();
			if (ans > res) ans = res;
		}
		REP(p, 0, L)
		{
			REP(i, 1, T) bg[i] = 0;e = 0;
			REP(i, 1, m) add(x[i], y[i], z[i]);
			REP(i, 1, k)
				if (im[i] >> p & 1)	add(im[i], T, 0);
				else				add(S, im[i], 0);
			int res = dij();
			if (ans > res) ans = res;
		}
		cout << ans << endl;
	}
	return 0;
}
