/*
 * File Name:	4016.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.25 17:11
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6, maxm = 1e6, inf = 1e8;

namespace Graph
{
	int bg[maxn], ne[maxm], to[maxm], c[maxm], w[maxm], e = 1;
	void add(int x, int y, int w, int c)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		Graph::w[e] = w;
		Graph::c[e] = c;
	}
	inline void Add(int x, int y, int w, int c = 0)
	{
		add(x, y, w, c);
		add(y, x, 0, -c);
	}
	int n, S, T;
	int dis[maxn], Max[maxn], frm[maxn];
	bool vis[maxn];
	queue <int> q;
	bool spfa()
	{
		while (!q.empty()) q.pop();
		REP(i, 1, n) dis[i] = inf, vis[i] = 0;
		q.push(S);
		dis[S] = 0;
		Max[S] = inf;
		while (!q.empty())
		{
			int x = q.front();q.pop();
			vis[x] = 0;
			for (int i = bg[x]; i; i = ne[i])
				if (w[i] > 0 && dis[to[i]] > dis[x] + c[i])
				{
					dis[to[i]] = dis[x] + c[i];
					Max[to[i]] = min(Max[x], w[i]);
					frm[to[i]] = i;
					if (!vis[to[i]])
					{
						vis[to[i]] = 1;
						q.push(to[i]);
					}
				}
		}
		return dis[T] < inf;
	}
	int min_cost;
	void update()
	{
		int x = T;
		while (x ^ S)
		{
			w[frm[x]] -= Max[T];
			w[frm[x] ^ 1] += Max[T];
			x = to[frm[x] ^ 1];
		}
		min_cost += dis[T] * Max[T];
	}
	void work() {while (spfa()) update();}
}
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

int n, a[maxn], sum, ave;

int main()
{
#ifdef CraZYali
	file("4016");
#endif
	n = read<int>();
	Graph::n = Graph::T = n + 2;
	Graph::S = n + 1;
	REP(i, 1, n) sum += (a[i] = read<int>());
	ave = sum / n;
	REP(i, 1, n)
		if (a[i] == ave) continue;
		else if (a[i] < ave) Graph::Add(i, Graph::T, ave - a[i]);
		else if (a[i] > ave) Graph::Add(Graph::S, i, a[i] - ave);
	REP(i, 1, n)
	{
		int le = (i == 1 ? n : i - 1);
		int ri = (i == n ? 1 : i + 1);
		Graph::Add(i, le, inf, 1);//a[i]);
		Graph::Add(i, ri, inf, 1);// a[i]);
	}
	Graph::work();
	cout << Graph::min_cost << endl;
	return 0;
}
