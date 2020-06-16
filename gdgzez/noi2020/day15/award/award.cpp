/*
	Problem:	award.cpp
	Time:		2020-06-16 10:25
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10;
const i64 inf = 1e18;

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

int n, a[maxn];
i64 dd[maxn];

i64 dis(i64 i, i64 j)
{
	if (i > j) swap(i, j);
	return dd[j] - dd[i];
}

bool vis[maxn];
i64 ans = inf;
void calc(i64 res)
{
	REP(i, 1, n) if (!vis[i]) return;
	chkmin(ans, res);
}
void dfs(int x, i64 y = 0)
{
	if (x == n) calc(y);
	else
	{
		x++;
		dfs(x, y);
		REP(i, 1, n) if (!vis[i])
		{
			vis[i] = 1;
			dfs(x, y + a[x] + dis(x, i));
			REP(j, i + 1, n) if (!vis[j])
			{
				vis[j] = 1;
				dfs(x, y + a[x] + a[x] + dis(x, i) + dis(x, j));
				vis[j] = 0;
			}
			vis[i] = 0;
		}
	}
}

namespace peach
{
	const int maxn = 1e6, maxm = 1e6;

	int bg[maxn], ne[maxm], to[maxm], w[maxm], e = 1;
	i64 cost[maxm];
	void add(int x, int y, int z, i64 c)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
		cost[e] = c;
	}
	void Add(int x, int y, int z, i64 c)
	{
		add(x, y, z, c);
		add(y, x, 0, -c);
	}

	int n, S, T;

	int fr[maxn], Max[maxn];
	i64 dis[maxn];
	queue <int> q;
	bool vis[maxn];
	bool spfa()
	{
		REP(i, 1, n) dis[i] = inf;
		dis[S] = 0;
		Max[S] = 1e9;
		q.push(S);
		while (!q.empty())
		{
			int x = q.front();
			vis[x] = 0;
			q.pop();
			for (int i = bg[x] ; i ; i = ne[i])
				if (w[i] > 0 && dis[to[i]] > dis[x] + cost[i])
				{
					dis[to[i]] = dis[x] + cost[i];
					Max[to[i]] = x;chkmin(Max[to[i]], w[i]);
					fr[to[i]] = i;
					if (!vis[to[i]])
					{
						vis[to[i]] = 1;
						q.push(to[i]);
					}
				}
		}
		return dis[T] != inf;
	}
	i64 min_cost, max_flow;
	void update()
	{
		int x = T;
		while (x ^ S)
		{
			w[fr[x]] -= Max[T];
			w[fr[x] ^ 1] += Max[T];
			x = to[fr[x] ^ 1];
		}
		min_cost += dis[T] * Max[T];
		max_flow += Max[T];
	}

	int id[maxn];
	int main()
	{
		REP(i, 1, ::n) id[i] = i;
		sort(id + 1, id + 1 + n, [](int x, int y) {return a[x] < a[y];});
	
		n = ::n * 2 + 2;
		S = n - 1;T = n;
		REP(i, 1, ::n) Add(S, id[i], 1, a[i]), Add(S, id[i], 1, a[i]);
		REP(i, 1, ::n)
			REP(j, 1, ::n) Add(id[i], id[j] + ::n, 1, :: dis(id[i], id[j]));
		REP(i, 1, ::n) Add(id[i] + ::n, T, 1, 0);
		while (spfa()) update();
		cout << min_cost << endl;
		return 0;
	}
}

namespace shit
{
	i64 ans ;
	priority_queue <i64, vector <i64>, greater <i64> > q1, q2;
	void ins1(i64 x, i64 y)
	{
		if (!q2.empty())
		{
			i64 tmp = q2.top();
			if (tmp + x + y < 0)
			{
				q2.pop();
				ans += tmp + x + y;
				q1.emplace(-tmp - x - x);
				q2.emplace(-x - y);
			}
			else q1.emplace(-x + y);
		}
		else q1.emplace(-x + y);
	}
	void ins2(i64 x)
	{
		i64 tmp = q1.top();q1.pop();
		ans += tmp + x;
		q2.emplace(-tmp - x - x);
	}
	int main()
	{
		REP(i, 1, n)
		{
			ins1(dd[i], a[i]);
			ins1(dd[i], a[i]);
			ins2(dd[i]);
		}
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("award");
#endif
	n = read<int>();
	REP(i, 2, n) dd[i] = read<int>() + dd[i - 1];
	REP(i, 1, n) a[i] = read<int>();
	return shit :: main();
	return peach :: main();
	dfs(0);
	cout << ans << endl;
	return 0;
}
