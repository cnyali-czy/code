/*
 * File Name:	3749.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.25 15:39
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 100 + 5;
const i64 inf = 1e18;
namespace Graph
{
	const int maxn = 10000 + 10, maxm = 20000 + 10;
	int n, S = 1, T = 2;
	int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
	i64 w[maxm << 1];
	void add(int x, int y, i64 z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
	void Add(int x, int y, i64 z)
	{
		add(x, y, z);
		add(y, x, 0);	
	}
	int dis[maxn], q[maxn], head, tail;
	bool bfs()
	{
		REP(i, 1, n) dis[i] = -1;
		dis[q[head = tail = 0] = T] = 0;
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
	i64 dfs(int x, i64 y)
	{
		if (x == T || !y) return y;
		i64 res = 0;
		for (int &i = cur[x]; i; i = ne[i])
			if (w[i] > 0 && dis[to[i]] == dis[x] - 1)
			{
				i64 tmp = dfs(to[i], min(y, w[i]));
				if (tmp > 0)
				{
					res += tmp;
					w[i] -= tmp;
					w[i ^ 1] += tmp;
					y -= tmp;
					if (!y) break;
				}
			}
		return res;
	}
	i64 Dinic()
	{
		i64 res = 0;
		while (bfs())
		{
			copy(bg, bg + 1 + n, cur);
			while (1)
			{
				i64 tmp = dfs(S, inf);
				if (!tmp) break;
				res += tmp;
			}
		}
		return res;
	}
}
using Graph::Add;
template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, a[maxn], id[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("3749");
#endif
	int &N = Graph::n;N = 2;
	cin >> n >> m;
	REP(i, 1, n)
	{
		a[i] = read<int>();
		chkmax(a[0], a[i]);
	}
	REP(i, 1, n)
		REP(j, i, n)
		id[i][j] = ++N;
	i64 ans = 0;
	REP(i, 1, n)
		REP(j, i, n)
		{
			int c = read<int>();
			if (i == j)
			{
				if (m) Add(id[i][j], N + a[i], inf);
				c -= a[i];
			}
			else
			{
				Add(id[i][j], id[i + 1][j], inf);
				Add(id[i][j], id[i][j - 1], inf);
			}
			if (c > 0)
			{
				Add(1, id[i][j], c);
				ans += c;
			}
			else if (c < 0)
				Add(id[i][j], 2, -c);
		}
	if (m)
		REP(i, 1, a[0]) Add(++N, 2, 1ll * i * i);
	cout << ans - Graph::Dinic() << endl;
	return 0;
}
