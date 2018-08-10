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
#include <stack>

using namespace std;

const int maxn = 20000 + 10, maxm = 50000 + 10;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, k;

int pre[maxn], low[maxn], belong[maxn];
int dfs_clock, scc_cnt;

stack <int> s;

void dfs(int u)
{
	s.push(u);
	pre[u] = low[u] = ++dfs_clock;
	for (register int i = bg[u]; i ; i = ne[i])
		if (!pre[to[i]])
		{
			dfs(to[i]);
			chkmin(low[u], low[to[i]]);
		}
		else if (!belong[to[i]]) chkmin(low[u], pre[to[i]]);
	if (low[u] == pre[u])
	{
		scc_cnt++;
		while (1)
		{
			register int x = s.top();
			s.pop();
			belong[x] = scc_cnt;
			if (x == u) break;
		}
	}
	
}

int in[maxn], out[maxn];

int main()
{
#ifdef CraZYali
	freopen("12167.in", "r", stdin);
	freopen("12167.out", "w", stdout);
#endif
	int T;
	cin >> T;
	
	while (T --> 0)
	{
		scanf("%d%d", &n, &m);
		e = 0;
		REP(i, 1, n) bg[i] = 0;
		while (m --> 0)
		{
			register int x, y;
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		scc_cnt = dfs_clock = 0;
		REP(i, 1, n) pre[i] = belong[i] = 0;
		REP(i, 1, n)
			if (!pre[i]) dfs(i);
		REP(i, 1, scc_cnt) in[i] = out[i] = 1;
		REP(x, 1, n)
			for (register int i = bg[x]; i ; i = ne[i])
				if (belong[x] ^ belong[to[i]]) in[belong[to[i]]] = 0, out[belong[x]] = 0;
		int A(0), B(0);
		REP(i, 1, scc_cnt)
		{
			A += in[i];
			B += out[i];
		}
		printf("%d\n", scc_cnt ^ 1 ? max(A, B) : 0);
	}
	return 0;
}
