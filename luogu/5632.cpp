/*
	Problem:	5632.cpp
	Time:		2020-12-04 16:09
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
#define int long long

using namespace std;
const int maxn = 600 + 5, maxm = maxn * maxn / 2, inf = 1e15;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

int n, m, S, T;
void clear()
{
	REP(i, 1, n + 2) bg[i] = 0;
	e = 1;
}
int X[maxm], Y[maxm], Z[maxm];

int q[maxn], head, tail, dis[maxn];
bool bfs()
{
	q[head = tail = 0] = T;
	REP(i, 1, n) dis[i] = -1;
	dis[T] = 1;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] == -1 && w[i ^ 1] > 0)
			{
				dis[to[i]] = dis[x] + 1;
				q[++tail] = to[i];
			}
	}
	return dis[S] != -1;
}
int cur[maxn];
int dfs(int x = S, int y = inf)
{
	if (x == T || !y) return y;
	int res = 0;
	for (int &i = cur[x]; i; i = ne[i]) if (dis[to[i]] == dis[x] - 1 && w[i] > 0)
	{
		int tmp = dfs(to[i], min(y, w[i]));
		if (tmp > 0)
		{
			res += tmp;
			y -= tmp;
			w[i] -= tmp;
			w[i ^ 1] += tmp;
			if (!y) break;
		}
	}
	return res;
}

signed main()
{
#ifdef CraZYali
	file("5632");
#endif
	n = read<int>();m = read<int>();S = n + 1;T = n + 2;
	REP(i, 1, m)
	{
		X[i] = read<int>();Y[i] = read<int>();Z[i] = read<int>();
	}
	int ans = inf;
	for (S = 1; S <= n; S++) for (T = S + 1; T <= n; T++)
	{
		clear();
		REP(i, 1, m)
		{
			add(X[i], Y[i], Z[i]);
			add(Y[i], X[i], Z[i]);
		}
		int res = 0;
		while (bfs())
		{
			copy(bg, bg + 1 + n, cur);
			int tmp = dfs();
			while (tmp > 0)
			{
				res += tmp;
				tmp = dfs();
			}
		}
		ans = min(ans, res);
	}
	cout << ans << endl;
	return 0;
}
