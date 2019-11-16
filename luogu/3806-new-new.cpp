/*
 * File Name:	3806-new-new.cpp
 * Author	:	CraZYali
 * Time		:	2019.11.16 16:15
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <map>

using namespace std;
const int maxn = 10000 + 10, maxm = 100 + 5;

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

int q[maxm], ans[maxm];

int siz[maxn], Max[maxn], rt, allnode;
bool vis[maxn];

void findrt(int x, int fa = -1)
{
	siz[x] = 1;
	Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		chkmax(Max[x], siz[to[i]]);
	}
	chkmax(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt]) rt = x;
}

int depth[maxn], dd[maxn], top;
#include <vector>
const int MOD = 19260817;
struct My_map
{
	int bg[MOD], ne[maxn], e;
	pair <int, int> to[maxn];
	inline void add(int x, int y)
	{
		e++;
		to[e] = make_pair(y, 1);
		ne[e] = bg[x];
		bg[x] = e;
	}
	bool vis[MOD];
	int have[MOD], top;
	inline bool clear()
	{
		REP(i, 1, top)
		{
			bg[have[i]] = 0;
			vis[have[i]] = 0;
		}
		top = e = 0;
	}
	inline int Hash(int x)
	{
		int res(0);
		do
		{
			res = res * 233 + x % 10;
			x /= 10;
		}while (x);
		return (MOD + res % MOD) % MOD;
	}
	inline int operator [] (int x)
	{
		int H(Hash(x));
		if (!vis[H]) return 0;
		for (int i = bg[H]; i; i = ne[i])
			if (to[i].first == x) return to[i].second;
		return 0;
	}
	inline void insert(int x)
	{
		int H(Hash(x));
		if (!vis[H])
		{
			vis[H] = 1;
			have[++top] = H;
		}
		for (int i = bg[H]; i; i = ne[i])
			if (to[i].first == x)
			{
				to[i].second++;
				return;
			}
		add(H, x);
	}
}cnt;

void get_depth(int x, int fa = -1)
{
	cnt.insert(depth[x]);
	dd[++top] = depth[x];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		depth[to[i]] = depth[x] + w[i];
		get_depth(to[i], x);
	}
}
int n, m;
void calc(int x, int d, int flag)
{
	top = 0;
	depth[x] = d;
	get_depth(x);
	REP(i, 1, top)
		REP(j, 1, m) if (q[j] >= dd[i]) ans[j] += flag * cnt[q[j] - dd[i]];
	cnt.clear();
}

void dfs(int x)
{
	vis[x] = 1;
	calc(x, 0, 1);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		calc(to[i], w[i], -1);
		allnode = siz[to[i]];
		rt = 0;
		findrt(to[i], x);
		dfs(rt);
	}
}

int main()
{
#ifdef CraZYali
	file("3806-new-new");
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	REP(i, 1, m) q[i] = read<int>();
	Max[0] = 1e9;
	allnode = n;
	findrt(1);
	dfs(rt);
	REP(i, 1, m)
		puts(ans[i] ? "AYE" : "NAY");
	return 0;
}
