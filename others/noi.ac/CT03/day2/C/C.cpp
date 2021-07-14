/*
	Problem:	C.cpp
	Time:		2021-07-12 11:50
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int inf = 1e9;

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

namespace Graph
{
	const int N = 50010, M = 30000000;

	int n, S, T;
	int h[N], e[M], f[M], ne[M], idx;
	int q[N], d[N], cur[N], A[N];

	void add(int a, int b, int c)
	{
		e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
		e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
	}

	bool bfs()
	{
		int hh = 0, tt = 0;
		memset(d, -1, sizeof d);
		q[0] = S, d[S] = 0, cur[S] = h[S];
		while (hh <= tt)
		{
			int t = q[hh ++ ];
			for (int i = h[t]; ~i; i = ne[i])
			{
				int ver = e[i];
				if (d[ver] == -1 && f[i])
				{
					d[ver] = d[t] + 1;
					cur[ver] = h[ver];
					if (ver == T) return true;
					q[ ++ tt] = ver;
				}
			}
		}
		return false;
	}

	int find(int u, int limit)
	{
		if (u == T) return limit;
		int flow = 0;
		for (int i = cur[u]; ~i && flow < limit; i = ne[i])
		{
			cur[u] = i;
			int ver = e[i];
			if (d[ver] == d[u] + 1 && f[i])
			{
				int t = find(ver, min(f[i], limit - flow));
				if (!t) d[ver] = -1;
				f[i] -= t, f[i ^ 1] += t, flow += t;
			}
		}
		return flow;
	}

	int dinic()
	{
		int r = 0, flow;
		while (bfs()) while (flow = find(S, inf)) r += flow;
		return r;
	}

	int s, t;
	void init(int n_, int s_, int t_)
	{
		n = n_;
		s = s_;
		t = t_;
		S = 0, T = n + 1;
	}
	inline void Add(int a, int b, int c, int d)
	{
		add(a, b, d - c);
		A[a] -= c, A[b] += c;
	}
	int calc()
	{
		int tot = 0;
		for (int i = 1; i <= n; i ++ )
			if (A[i] > 0) add(S, i, A[i]), tot += A[i];
			else if (A[i] < 0) add(i, T, -A[i]);

		add(t, s, inf);

		if (dinic() < tot) return -1;
		else
		{
			int res = f[idx - 1];
			S = t, T = s;
			f[idx - 1] = f[idx - 2] = 0;
			return res - dinic();
		}
	}
}

namespace run
{
	const int maxn = 5000 + 10, maxq = 5000 + 10;

	int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
	inline void add(int x, int y, int z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
	int dis[maxn][maxn], *d;
	void dfs(int x, int fa = 0)
	{
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			d[to[i]] = d[x] + w[i];
			dfs(to[i], x);
		}
	}

	int n, q, A[maxq], B[maxq], C[maxq], t[maxq], k;
	unordered_map <int, int> need[maxq];
	map <int, int> ed[maxn];
	int st[maxn];
#define fi first
#define se second
	int main()
	{
		memset(Graph :: h, -1, sizeof Graph :: h);
		n = read<int>();
		REP(i, 2, n)
		{
			int x = read<int>(), y = read<int>(), z = read<int>();
			add(x, y, z);add(y, x, z);
		}
		REP(i, 1, n)
		{
			d = dis[i];
			dfs(i);
		}
		q = read<int>();
		REP(i, 1, q)
		{
			t[i] = A[i] = read<int>();
			B[i] = read<int>();C[i] = read<int>();			
		}
		sort(t + 1, t + 1 + q);k = unique(t + 1, t + 1 + q) - t - 1;
		REP(i, 1, q) A[i] = lower_bound(t + 1, t + 1 + k, A[i]) - t;
		REP(i, 1, q) need[A[i]][C[i]] += B[i];
		int N = 0, S, T;
		//先不管源点汇点
		REP(i, 1, k)
		{
			static int in[maxn], ou[maxn];
			for (auto j : need[i])
			{
				in[j.fi] = ++N;//这个是收入点
				ou[j.fi] = ++N;//这个是中转点
				if (i == 1) continue;
				REP(k, 1, n) if (ed[k].size())
				{
					int l = 1, r = i - 1, gdlt = -1;
					while (l <= r)
					{
						int mid = l + r >> 1;
						auto it = ed[k].lower_bound(mid);
						if (it == ed[k].end() || dis[j.fi][k] > t[i] - t[it -> fi])
						{
							r = mid - 1;
							continue;
						}
						gdlt = it -> se;
						l = mid + 1;
					}
					if (~gdlt) Graph :: Add(gdlt, in[j.fi], 0, inf);
					/*
					DEP(lt, i - 1, 1)
					if (ed[k].find(lt) != ed[k].end() && dis[j.fi][k] <= t[i] - t[lt])
					{
						Graph :: Add(ed[k][lt], in[j.fi], 0, inf);
						break;
					}*/
				}
			}
			for (auto j : need[i])
			{
				Graph :: Add(in[j.fi], ou[j.fi], j.se, inf);
				if (!st[j.fi]) st[j.fi] = in[j.fi];
				ed[j.fi][i] = ou[j.fi];
			}
		}
		S = ++N;T = ++N;
		REP(i, 1, n)
		{
			if (st[i]) Graph :: Add(S, st[i], 0, inf);
			DEP(j, k, 1) if (ed[i].find(j) != ed[i].end())
			{
				Graph :: Add(ed[i][j], T, 0, inf);
				break;
			}
		}
		Graph :: init(N, S, T);
		cout << Graph :: calc() << endl;
		return 0;
	}
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	return run :: main();
}
