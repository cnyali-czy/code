#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 1000 + 10, maxm = 10000 + 10, inf = 1e9;

struct edge
{
	int u, v, w;
}e[maxm];
int n, m, k;
int id[maxn], pre[maxn], vis[maxn], in[maxn];
inline int solve(int root)
{
	register int ret = 0;
	while (1)
	{
		REP(i, 1, n) in[i] = inf;
		REP(i, 1, m)
			if (e[i].u ^ e[i].v && in[e[i].v] > e[i].w) in[e[i].v] = e[i].w, pre[e[i].v] = e[i].u;
		REP(i, 1, n) if (i ^ root && in[i] == inf) return -1;
		
		register int cnt = 1;
		in[root] = 0;
		REP(i, 1, n) id[i] = vis[i] = 0;
		REP(i, 1, n)
		{
			ret += in[i];
			register int v = i;
			while (v ^ root && !id[v] && vis[v] ^ i) {vis[v] = i;v = pre[v];}
			if (v ^ root && !id[v])
			{
				for (register int u = pre[v]; u ^ v; u = pre[u]) id[u] = cnt;
				id[v] = cnt++;
			}
		}
		if (!(--cnt)) return ret;
		REP(i, 1, n) if (!id[i]) id[i] = ++cnt;

		for (register int i = 1 ; i <= m;)
		{
			int v = e[i].v;
			e[i].u = id[e[i].u];
			e[i].v = id[e[i].v];
			if (e[i].u ^ e[i].v) e[i++].w -= in[v];
			else swap(e[i], e[m--]);
		}
		n = cnt;
		root = id[root];
	}
	return ret;
}

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int main()
{
#ifdef CraZYali
	freopen("IamyourFather.in", "r", stdin);
	freopen("IamyourFather.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();
		m = read<int>();
		REP(i, 1, m)
		{
			e[i] = (edge){read<int>(), read<int>(), read<int>() * -1000};
			if (e[i].v == n) e[i].w += e[i].u - 1;
		}
		int ans = solve(1);
		printf("%d %d\n", (-ans + 999) / 1000, (-ans + 999) / 1000 * 1000 + ans + 1);
	}

	return 0;
}

