/*
	Problem:	treasure.cpp
	Time:		2020-06-13 08:22
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 405, maxN = (maxn << 16) + maxn, maxm = 1e5 + 10, maxM = 6.5e7;

int bg[maxN], ne[maxM], to[maxM], w[maxM], e;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, k;
int x[maxm], y[maxm], z[maxm], key[20], id[maxn];

inline int Id(int S, int x) {return S * n + x;}
inline bool ok(int S, int x)
{
	if (!id[x]) return 1;
	return S >> (id[x] - 1) & 1;
}

const int inf = (1ll << 31) - 1;
int dis[maxN];
struct node
{
	int x, d;
	inline node(int x = 0, int d = 0) : x(x), d(d) {}
	inline bool operator < (const node &B) const {return d > B.d;}
};
priority_queue <node> q;
int N;
bitset <maxn> vis;

int dij(int s, int t)
{
	if (!ok(0, s)) return -1;
	while (!q.empty()) q.pop();
	REP(i, 1, N) dis[i] = inf;
	vis.reset();
	dis[s] = 0;
	q.emplace(s, 0);
	t %= n;
	while (!q.empty())
	{
		auto qaq = q.top();q.pop();
		int x = qaq.x;int d = qaq.d;
		if (x % n == t) return d;
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = bg[x]; i; i = ne[i])
			if (!vis[to[i]] && dis[to[i]] > d + w[i])
			{
				dis[to[i]] = d + w[i];
				q.emplace(to[i], dis[to[i]]);
			}
	}
//	REP(i, 1, N) printf("%lld%c", dis[i], i == N ? '\n' : ' ');
	return -1;
}

int main()
{
#ifdef CraZYali
	file("treasure");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, m) x[i] = read<int>(), y[i] = read<int>(), z[i] = read<int>();
	REP(i, 1, k) id[read<int>()] = i, key[i] = read<int>();
	REP(S, 0, (1 << k) - 1)
	{
		REP(i, 1, m)
		{
			int x = ::x[i], y = ::y[i], z = ::z[i];
			if (ok(S, x) && ok(S, y)) 
			{
				add(Id(S, x), Id(S, y), z);
				add(Id(S, y), Id(S, x), z);
			}
		}
		REP(i, 1, k) if (ok(S, key[i]) && !(S >> (i - 1) & 1))
			add(Id(S, key[i]), Id(S | (1 << i - 1), key[i]), 0);
	}
	N = n << k;
//	REP(x, 1, N) for (int i = bg[x]; i; i = ne[i]) printf("%d %d %d\n", x, to[i], w[i]);
	int q = read<int>();
	while (q--)
	{
		int s = read<int>(), t = read<int>();
		printf("%d\n", dij(s, t));
	}
	return 0;
}
