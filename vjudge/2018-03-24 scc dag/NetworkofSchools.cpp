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
const int maxn = 100 + 5, maxm = maxn * maxn;

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
int m, n, k;

int belong[maxn], cnt;
bool vis[maxn];

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], e;
	Graph() {memset(bg, 0, sizeof(bg)); e = 0;}
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}

	void dfs(int x, bool mode)
	{
		if (!mode) vis[x] = 1;
		else belong[x] = cnt;
		for (register int i = bg[x]; i ; i = ne[i])
			if (!mode && !vis[to[i]] && !belong[to[i]]) dfs(to[i], 0);
			else if (mode && vis[to[i]] && !belong[to[i]]) dfs(to[i], 1);
	}
}A, B;

inline void get_belong()
{
	REP(i, 1, n)
		if (!belong[i])
		{
			cnt++;
			memset(vis, 0, sizeof(vis));
			A.dfs(i, 0);
			B.dfs(i, 1);
		}
}

map <pair<int, int>, bool> Vis;

int in[maxn], out[maxn];

int main()
{
#ifdef CraZYali
	freopen("NetworkofSchools.in", "r", stdin);
	freopen("NetworkofSchools.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		register int x(read<int>());
		while (x)
		{
			A.add(i, x);B.add(x, i);
			x = read<int>();
		}
	}
	get_belong();
	if (cnt == 1) cout << 1 << endl << 0;
	else
	{
		REP(x, 1, n)
			for (register int i = A.bg[x]; i ; i = A.ne[i])
				if (belong[x] ^ belong[A.to[i]] && !Vis[make_pair(belong[x], belong[A.to[i]])])
				{
					Vis[make_pair(belong[x], belong[A.to[i]])] = 1;
					out[belong[x]]++;in[belong[A.to[i]]]++;
				}
		int c_in(0), c_out(0);
		REP(i, 1, cnt)
		{
			if (!in[i]) c_in++;
			if (!out[i]) c_out++;
		}
		printf("%d\n%d", c_in, max(c_in, c_out));
	}
	return 0;
}
