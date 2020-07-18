/*
	Problem:	B.cpp
	Time:		2020-07-16 23:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <deque>
#include <ctime>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 500 + 5;
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

int n, q, a[maxn][maxn];
i64 Ans[maxn];

namespace Graph
{
	int N, S, SS, T;
	const int maxn = ::maxn << 1, maxm = ::maxn * ::maxn;
	int lst[maxn], bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], cost[maxm << 1], e = 1;
	inline void add(int x, int y, int z, int c)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
		cost[e] = c;
	}
	inline void Add(int x, int y, int z, int c)
	{
		add(x, y, z, c);
		add(y, x, 0, -c);
	}
	i64 dis[maxn], ans;
	int pre[maxn], Max[maxn];
	bool vis[maxn];
	deque <int> q;
	bool spfa()
	{
		REP(i, 1, N) dis[i] = -inf, Max[i] = 0;
		Max[SS] = 1e9;dis[SS] = 0;
		q.push_back(SS);
		while (!q.empty())
		{
			int x = q.front();q.pop_front();
			vis[x] = 0;
			if (!Max[x]) continue;
			for (int i = lst[x]; i; i = ne[i])
				if (w[i] > 0 && dis[to[i]] < dis[x] + cost[i])
				{
					dis[to[i]] = dis[x] + cost[i];
					Max[to[i]] = 1;
					pre[to[i]] = i;
					if (!vis[to[i]]) q.push_back(to[i]), vis[to[i]] = 1;
				}
		}
//		REP(i, 1, N) printf("%d%c", dis[i], i == end_i ? '\n' : ' ');
		return dis[T] > 0;
	}
	void update()
	{
		ans += dis[T];
		int x = T;
		while (x ^ SS)
		{
			w[pre[x]]--;
			w[pre[x] ^ 1]++;
			x = to[pre[x] ^ 1];
		}
	}
	int dfs(int x, int y)
	{
		if (x == T) {vis[T] = 1;return y;}
		int used = 0;
		vis[x] = 1;
		for (int i = bg[x]; i; i = ne[i])
			if (!vis[to[i]] && w[i] > 0 && dis[to[i]] == dis[x] + cost[i])
			{
				int tmp = dfs(to[i], min(w[i], y));
				if (tmp > 0)
				{
					w[i] -= tmp;
					w[i ^ 1] += tmp;
					used += tmp;
					if (used == y) break;
				}
			}
		return used;
	}
	int id[maxn];
	void work()
	{
		S = n + n + 1;
		SS = S + 1;
		N = T = SS + 1;
		Add(SS, S, 0, 0);
		REP(i, 1, n) Add(S, i, 1, 0);
		REP(i, 1, n)
		{
			REP(j, 1, n) id[j] = j;
			random_shuffle(id + 1, id + 1 + n);
			REP(j, 1, n)
				Add(i, id[j] + n, 1, a[i][id[j]]);
		}
		REP(i, 1, n) Add(i + n, T, 1, 0);
		REP(i, 1, N) lst[i] = bg[i];
		REP(i, 1, n)
		{
			w[2]++;
			while (spfa())
			{
				vis[T] = 1;
				while (vis[T])
				{
					memset(vis, 0, sizeof vis);
					ans += dfs(SS, 1e9);
				}
			}
			Ans[i] = ans;
		}
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	read<int>();
	n = read<int>();q = read<int>();
	REP(i, 1, n) REP(j, 1, n) a[i][j] = read<int>();
	Graph :: work();
	while (q--) printf("%lld.0\n", Ans[min(read<int>(), n)]);
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
