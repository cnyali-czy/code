/*
	Problem:	C.cpp
	Time:		2020-06-09 15:11
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
const int maxn = 1e6, N = 200, inf = 1e8;

int n, m, cur[maxn], bg[maxn], ne[maxn], to[maxn], w[maxn], e = 1;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int dis[maxn], S, T, q[maxn], head, tail;
bool bfs()
{
	REP(i, 1, T) dis[i] = -1;
	dis[q[head = tail = 0] = T] = 0;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i; i = ne[i])
			if (dis[to[i]] == -1 && w[i ^ 1] > 0)
				dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[S] > 0;
}
int dfs(int x = S, int y = inf)
{
	if (x == T || !y) return y;
	int res = 0;
	for (int &i = cur[x]; i; i = ne[i])
		if (dis[to[i]] == dis[x] - 1 && w[i] > 0)
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

int dinic()
{
	int ans = 0;
	while (bfs())
	{
		copy(bg, bg + n + n + 3, cur);
		int tmp = dfs();
		while (tmp > 0)
		{
			ans += tmp;
			tmp = dfs();
		}
	}
	return ans;
}
int a[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	int ans = 0;
	REP(i, 1, n)
	{
		a[i] = read<int>() + N;
		ans += a[i];
	}
	S = n + n + 1;T = n + n + 2;
	REP(i, 1, n)
	{
		Add(S, i, a[i]);
		Add(i + n, T, a[i]);
		Add(i, i + n, N);
	}
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		Add(x, y, inf);
		Add(x + n, y + n, inf);
	}
	cout << ans - dinic() << endl;
	return 0;
}
