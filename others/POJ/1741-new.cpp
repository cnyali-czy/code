/*
 * File Name:	1741-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.18 21:10
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 100000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

int n, k, ans;

bool vis[maxn];

inline void clear()
{
	e = 0;
	REP(i, 1, n) bg[i] = vis[i] = 0;
	ans = 0;
}

int allnode, rt, Max[maxn], siz[maxn];
void getrt(int x, int fa = -1)
{
	siz[x] = 1;
	Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		getrt(to[i], x);
		siz[x] += siz[to[i]];
		chkmax(Max[x], siz[to[i]]);
	}
	chkmax(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt]) rt = x;
}

int depth[maxn];

int v[maxn], vv;

void get_depth(int x, int fa = -1)
{
	if (depth[x] > k) return;
	v[++vv] = depth[x];
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
	{
		depth[to[i]] = depth[x] + w[i];
		get_depth(to[i], x);
	}
}

inline int calc(int x, int d = 0)
{
	vv = 0;
	depth[x] = d;
	get_depth(x);
	sort(v + 1, v + 1 + vv);
	int res(0);
	REP(i, 2, vv)
		res += upper_bound(v + 1, v + i, k - v[i]) - v - 1;
	return res;
}
void dfs(int x)
{
	vis[x] = 1;
	ans += calc(x);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		ans -= calc(to[i], w[i]);
		allnode = siz[to[i]];
		rt = 0;
		getrt(to[i], x);
		dfs(rt);
	}
}

int main()
{
#ifdef CraZYali
	file("1741-new");
#endif
	Max[0] = 1e9;
	while (scanf("%d%d", &n, &k) != EOF && (n + k))
	{
		clear();
		REP(i, 2, n)
		{
			int x(read<int>()), y(read<int>()), z(read<int>());
			add(x, y, z);add(y, x, z);
		}
		allnode = n;
		rt = 0;
		getrt(1);
		dfs(rt);
		printf("%d\n", ans);
	}
	return 0;
}
