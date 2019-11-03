/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.31 19:10
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10, maxm = 2e6 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	e++;
	to[e] = x;
	ne[e] = bg[y];
	bg[y] = e;
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

int n, m, k, ans;

int fa[maxn], siz[maxn], ed[maxn];
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) ed[x]++;
	else
	{
		ed[y] += ed[x] + 1;
		siz[y] += siz[x];
		fa[x] = y;
	}
}
inline int count_sets()
{
	int res(0);
	REP(i, 1, n) res += (i == fa[i]);
	return res;
}

namespace cheat
{
	bool vis[maxn];
	int dep[maxn], mark[maxn];
	pair <int, int> tofa[maxn];
	void dfs(int u, int fa = -1)
	{
		vis[u] = 1;
		for (int i = bg[u], v = to[i]; i; v = to[i = ne[i]]) if (v ^ fa)
			if (!vis[v])
			{
				dep[v] = dep[u] + 1;
				tofa[v] = make_pair(u, v);
				dfs(v, u);
			}
			else
				if (dep[u] < dep[v]) mark[u]--, mark[v]++;
				else mark[v]--, mark[u]++;
	}
	int bridge_cnt;
	inline void new_add(int u, int v)
	{
		uni(u, v);
		bridge_cnt--;
	}
	void calc(int u, int fa = -1)
	{
		for (int i = bg[u], v = to[i]; i; v = to[i = ne[i]]) if (dep[v] == dep[u] + 1)
		{
			calc(v, u);
			mark[u] += mark[v];
		}
		else if (dep[u] < dep[v] && v != fa) new_add(u, v);
		if (mark[u])
			new_add(tofa[u].first, tofa[u].second);
	}

	int DIS[maxn], QAQ[maxn], QAQ_TOP;
	void dfs2(int x, int fa = -1)
	{
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			if (!DIS[to[i]])
			{
				DIS[to[i]] = DIS[x] + 1;
				dfs2(to[i], x);
			}
			else if (DIS[to[i]] < DIS[x] + 1) QAQ[++QAQ_TOP] = DIS[x] - DIS[to[i]] + 1;
		}
	}

	inline void work()
	{
		REP(i, 1, n) ed[i] = 0, siz[fa[i] = i] = 1;
		bridge_cnt = m;
		REP(i, 1, n)
			if (!vis[i])
			{
				dep[i] = 1;
				dfs(i);
				calc(i);
			}
#ifdef CraZYali
		cout << bridge_cnt << endl;
		//REP(i, 1, n) if (i == fa[i])
		//	assert(ed[i] == siz[i] || ed[i] == siz[i] - 1);
		puts("------");
#endif
		if (bridge_cnt >= k)
		{
			ans += k;
			return;
		}
		ans += bridge_cnt;
		k -= bridge_cnt;
		REP(i, 1, n)
			if (!DIS[i])
			{
				DIS[i] = 1;
				dfs2(i);
			}
		vector <int> ccc, cnt;
		cnt = vector <int> (n + 1, 0);
		int ttt(0);
		REP(i, 1, QAQ_TOP) cnt[QAQ[i]]++, ttt++;
		ccc = vector<int>(ttt);
		ttt = 0;
		DREP(i, n, 1)
			while (cnt[i]--) ccc[ttt++] = i;
		for (int qaq : ccc)
		{
			if (k > qaq)
			{
				k -= qaq;
				ans += qaq - 1;
			}
			else
			{
				ans += k - 1;
				return;
			}
		}
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m >> k;
	REP(i, 1, n) siz[fa[i] = i] = 1;
	REP(i, 1, m)
	{
		int u(read<int>()), v(read<int>());
		add(u, v);
		uni(u, v);
	}

	ans = count_sets();
	if (k) cheat::work();
	cout << ans << endl;
	return 0;
}
