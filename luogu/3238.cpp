/*
	Problem:	F.cpp
	Time:		2021-05-02 19:23
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
#include <queue>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 2e5 + 10, maxm = 2e5 + 10, inf = 1e16;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
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

int n, m, q, u[maxm], v[maxm];

int frm[maxn], d1[maxn], dn[maxn];
struct node
{
	int x, d;
	node() {}
	node(int x, int d) : x(x), d(d) {}
	inline bool operator < (const node &B) const {return d > B.d;}
};
priority_queue <node> que;
vector <pair <int, int> > gg[maxn];
void dij(int dis[], int s)
{
	REP(i, 1, n) frm[i] = 0;
	REP(i, 1, n) dis[i] = inf;
	que.emplace(s, dis[s] = 0);
	while (que.size())
	{
		auto Node = que.top();que.pop();
		int x = Node.x, d = Node.d;
		if (d > dis[x]) continue;
		if (s == 1)
		{
			for (int i = bg[x]; i; i = ne[i])
				if (dis[to[i]] > d + w[i])
				{
					dis[to[i]] = d + w[i];
					frm[to[i]] = i;
					que.emplace(to[i], dis[to[i]]);
				}
		}
		else
		{
			for (auto E : gg[x])
			{
				int y = E.first, w = E.second;
				if (dis[y] > d + w)
				{
					dis[y] = d + w;
					que.emplace(y, dis[y]);
				}
			}
		}
	}
}
bool isfrm[maxn];
vector <int> T[maxn];
int siz[maxn], dfn[maxn], dfs_clock;
void dfs(int x)
{
	dfn[x] = ++dfs_clock;
	siz[x] = 1;
	for (int y : T[x])
	{
		dfs(y);
		siz[x] += siz[y];
	}
}
inline bool in(int x, int y) {return dfn[y] <= dfn[x] && dfn[x] <= dfn[y] + siz[y] - 1;}//x in subtree(y) 

namespace SMT
{
	int Min[maxn << 2];
	map <int, int> pzk[maxn << 2];
	void init()
	{
		REP(i, 0, n << 2) Min[i] = inf, pzk[i].clear();
	}
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
	void update(int p, int l, int r, int pos, int val, int flg)
	{
		if (l == r)
		{
			pzk[p][val] += flg;
			if (!(pzk[p].begin() -> second)) pzk[p].erase(pzk[p].begin());
			Min[p] = pzk[p].size() ? pzk[p].begin() -> first : inf ;
		}
		else
		{
			if (pos <= mid) update(lson, pos, val, flg);
			else update(rson, pos, val, flg);
			Min[p] = min(Min[ls], Min[rs]);			
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return Min[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return min(query(lson, L, R), query(rson, L, R));
		}
	}
}
int ans[maxn];

struct skydogli
{
	int id, l, r, ban;
	skydogli() {}
	skydogli(int id, int l, int r, int ban) : id(id), l(l), r(r), ban(ban) {}
};
vector <skydogli> v1[maxn], v2[maxn];
vector <pair <int, int> > vec[maxn];

signed main()
{
#ifdef CraZYali
	file("3238");
#endif
	cin >> n >> m >> q;
	REP(i, 1, m)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		u[i] = x;v[i] = y;
		add(x, y, z);add(y, x, inf);
		gg[y].emplace_back(x, z);
	}
	dij(dn, n);
	dij(d1, 1);
	if (d1[n] >= inf / 2)
	{
		while (q--) puts("-1");
		return 0;
	}
	for (int x = n; x ^ 1; x = to[frm[x] ^ 1]) isfrm[frm[x] >> 1] = 1;
	REP(i, 2, n) T[to[frm[i] ^ 1]].emplace_back(i);
	dfs(1);


	REP(Case, 1, q)
	{
		int t = read<int>(), x = inf;
		if (!isfrm[t]) ans[Case] = min(d1[n], d1[u[t]] + x + dn[v[t]]);
		else if (x <= v[t]) ans[Case] = d1[u[t]] + x + dn[v[t]];
		else
		{
			ans[Case] = d1[n] + x - w[t << 1];

			int p = siz[u[t]] < siz[v[t]] ? u[t] : v[t], f = u[t] + v[t] - p;

			int &res = ans[Case];
			REP(i, 1, m) if (i ^ t)
			{
				if (!in(u[i], p) && in(v[i], p))
					res = min(res, d1[u[i]] + w[i << 1] + dn[v[i]]);
			}

			v1[dfn[p] - 1		].emplace_back(Case, dfn[p], dfn[p] + siz[p] - 1, t);
			v2[dfn[p] + siz[p]	].emplace_back(Case, dfn[p], dfn[p] + siz[p] - 1, t);
		}
	}

	REP(t, 1, m)
	{
		vec[dfn[u[t]]].emplace_back(dfn[v[t]], d1[u[t]] + w[t << 1] + dn[v[t]]);
		//	vec[dfn[v[t]]].emplace_back(dfn[u[t]], d1[v[t]] + w[t << 1] + dn[u[t]]);
	}
	SMT :: init();
	REP(x, 1, n)
	{
		for (auto Node : vec[x]) SMT :: update(1, 1, n, Node.first, Node.second, 1);
		for (auto Q : v1[x])
		{
			int t = Q.ban;
			if (dfn[u[t]] <= x) SMT :: update(1, 1, n, dfn[v[t]], d1[u[t]] + w[t << 1] + dn[v[t]], -1);
			//		if (dfn[v[t]] <= x) SMT :: update(1, 1, n, dfn[u[t]], d1[v[t]] + w[t << 1] + dn[u[t]], -1);

			//			ans[Q.id] = min(ans[Q.id], SMT :: query(1, 1, n, Q.l, Q.r));

			if (dfn[u[t]] <= x) SMT :: update(1, 1, n, dfn[v[t]], d1[u[t]] + w[t << 1] + dn[v[t]], 1);
			//		if (dfn[v[t]] <= x) SMT :: update(1, 1, n, dfn[u[t]], d1[v[t]] + w[t << 1] + dn[u[t]], 1);
		}
	}
	SMT :: init();
	DEP(x, n, 1)
	{
		for (auto Node : vec[x]) SMT :: update(1, 1, n, Node.first, Node.second, 1);
		for (auto Q : v2[x])
		{
			int t = Q.ban;
			if (dfn[u[t]] >= x) SMT :: update(1, 1, n, dfn[v[t]], d1[u[t]] + w[t << 1] + dn[v[t]], -1);
			//		if (dfn[v[t]] >= x) SMT :: update(1, 1, n, dfn[u[t]], d1[v[t]] + w[t << 1] + dn[u[t]], -1);

			//			ans[Q.id] = min(ans[Q.id], SMT :: query(1, 1, n, Q.l, Q.r));

			if (dfn[u[t]] >= x) SMT :: update(1, 1, n, dfn[v[t]], d1[u[t]] + w[t << 1] + dn[v[t]], 1);
			//		if (dfn[v[t]] >= x) SMT :: update(1, 1, n, dfn[u[t]], d1[v[t]] + w[t << 1] + dn[u[t]], 1);
		}
	}

	REP(i, 1, q) printf("%lld\n", ans[i] < inf / 2 ? ans[i] : -1);
	return 0;
}

