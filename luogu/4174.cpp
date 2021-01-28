/*
	Problem:	4174.cpp
	Time:		2021-01-28 08:28
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
const int maxn = 5000 + 10, maxm = 50000 + 10, maxN = maxn + maxm, maxM = 3 * maxm + maxn, inf = 1e9;

int bg[maxN], ne[maxM << 1], to[maxM << 1], w[maxM << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
inline void Add(int x, int y, int z)
{
	add(x, y, z);
	add(y, x, 0);
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
int dis[maxN];

bool bfs()
{
	static int que[maxN], head, tail;
	REP(i, 1, T) dis[i] = -1;
	que[head = tail = 0] = T;
	dis[T] = 0;
	while (head <= tail)
	{
		int x = que[head++];
		for (int i = bg[x]; i; i = ne[i]) if (w[i ^ 1] > 0 && dis[to[i]] == -1)
			dis[que[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[S] != -1;
}
int cur[maxN];
int dfs(int x, int y = inf)
{
	if (x == T || !y) return y;
	int res = 0;
	for (int &i = cur[x]; i; i = ne[i])
		if (w[i] > 0 && dis[to[i]] == dis[x] - 1)
		{
			int tmp = dfs(to[i], min(y, w[i]));
			if (tmp > 0)
			{
				y -= tmp;
				w[i] -= tmp;
				w[i ^ 1] += tmp;
				res += tmp;
				if (!y) break;
			}
		}
	return res;
}

signed main()
{
#ifdef CraZYali
	file("4174");
#endif
	n = read<int>();m = read<int>();
	int ans = 0;
	S = n + m + 1;T = n + m + 2;
	REP(i, 1, n) Add(S, i, read<int>());
	REP(i, 1, m)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		Add(x, i + n, inf);Add(y, i + n, inf);
		Add(i + n, T, z);
		ans += z;
	}
	while (bfs())
	{
		copy(bg, bg + T, cur);
		int tmp = dfs(S, inf);
		while (tmp)
		{
			ans -= tmp;
			tmp = dfs(S, inf);
		}
	}
	cout << ans << endl;
	return 0;
}
