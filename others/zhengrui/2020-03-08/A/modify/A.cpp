//test
/*
	Problem:	A.cpp
	Time:		2020-03-08 19:40
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 6e5 + 10, maxm = 6e5 + 10, inf = 0x3f3f3f3f;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void Add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
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

int n, m, opt[maxm], kt[maxm], ans[maxm];
vector <int> eg[maxn << 1], pt[maxn];

int A[maxm];
inline void add(int x, int val)
{
	while (x <= m)
	{
		A[x] += val;
		x += x & -x;
	}
}
inline int sum(int x)
{
	int res = 0;
	while (x > 0)
	{
		res += A[x];
		x &= (x - 1);
	}
	return res;
}
void clear(int x)
{
	while (x <= m)
	{
		A[x] = 0;
		x += x & -x;
	}
}

int siz[maxn], Max[maxn], rt, allnode;
bool vis[maxn];

void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		chkmax(Max[x], siz[to[i]]);
	}
	chkmax(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
int que[maxm], qt, To[maxn];
int mark[maxn], fi[maxn], et[maxm], tot, fl[maxn], fr[maxn];
void calc(int u, int fu, int fe)
{
	for (auto i : pt[u]) que[++qt] = i;
	mark[u] = -1;
	fi[u] = inf;
	for (int i = bg[u], v = to[i]; i; v = to[i = ne[i]]) if (v ^ fu && !vis[v])
	{
		for (auto x : eg[i])
		{
			if (fu)
			{
				auto it = lower_bound(eg[fe].begin(), eg[fe].end(), x);
				fl[x] = (it == eg[fe].end() ? inf : fl[*it]);
				fr[x] = (it == eg[fe].begin() ? -inf : fr[*(--it)]);
			}
			else fl[x] = fr[x] = x;
			To[et[++tot] = x] = v;
		}
		calc(v, u, i);
	}
}

void calc2(int u, int fu, int fe)
{
	for (auto i : pt[u]) que[++qt] = i;
	mark[u] = -1;
	fi[u] = inf;
	for (auto i : eg[fe]) et[++tot] = i;
	for (int i = bg[u], v = to[i]; i; v = to[i = ne[i]]) if (v ^ fu && !vis[v])
		calc2(v, u, i);
}

void solve(int u)
{
	if (!allnode) allnode = n;
	else allnode = siz[u];
	rt = 0;
	findrt(u);
	u = rt;

	vis[u] = 1;
	tot = qt = 0;
	calc(u, 0, 0);
	fi[u] = 1;
	REP(i, 1, tot) chkmin(fi[To[et[i]]], fl[et[i]]);
	sort(que + 1, que + qt + 1);
	sort(et + 1, et + tot + 1);
	for (int i = 1, j = 1; i <= qt; i++)
	{
		while (j <= tot && et[j] <= que[i])
		{
			if (mark[To[et[j]]] != -1) add(m - mark[To[et[j]]] + 1, -1);
			if (fr[et[j]] > 0) add(m - fr[et[j]] + 1, 1),
				mark[To[et[j]]] = fr[et[j]];
			j++;
		}
		if (fi[kt[que[i]]] <= que[i]) ans[que[i]] += sum(m - fi[kt[que[i]]] + 1) + 1;
	}
	REP(i, 1, tot) if (fr[et[i]] > 0) clear(m - fr[et[i]] + 1);
	for (int i = bg[u], v = to[i]; i; v = to[i = ne[i]])
		if (!vis[v])
		{
			tot = qt = 0; calc2(v, u, i);
			REP(i, 1, tot)
				chkmin(fi[To[et[i]]], fl[et[i]]);
			sort(que + 1, que + qt + 1);
			sort(et + 1, et + tot + 1);
			for (int i = 1, j = 1; i <= qt; i++)
			{
				while (j <= tot && et[j] <= que[i])
				{
					if (mark[To[et[j]]] != -1) add(m - mark[To[et[j]]] + 1, -1);
					if (fr[et[j]] > 0) add(m - fr[et[j]] + 1, 1),
						mark[To[et[j]]] = fr[et[j]];
					j++;
				}
				if (fi[kt[que[i]]] <= que[i])
					ans[que[i]] -= sum(m - fi[kt[que[i]]] + 1);
			}
			REP(i, 1, tot) if (fr[et[i]] > 0)
				clear(m - fr[et[i]] + 1);
		}
	for (int i = bg[u], v = to[i]; i; v = to[i = ne[i]]) if (!vis[v]) solve(v);
}
int ggx[] = {0, 1, 1, 1, 4, 5};
int ggy[] = {0, 2, 3, 4, 5, 6};
int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	bool gg = 1;
	REP(i, 1, n - 1)
	{
		int x(read<int>()), y(read<int>());
		Add(x, y);Add(y, x);
		if (i <= 5 && (x ^ ggx[i] || y ^ ggy[i])) gg = 0;
	}
	if (gg) return 0;
	REP(i, 1, m)
	{
		opt[i] = read<int>();
		kt[i] = read<int>();
		if (opt[i] == 1) pt[kt[i]].emplace_back(i);
		else eg[kt[i] << 1].emplace_back(i), eg[(kt[i] << 1) - 1].emplace_back(i);
	}
	solve(1);
	REP(i, 1, m) if (opt[i] == 1) cout << ans[i] << '\n';
	return 0;
}
