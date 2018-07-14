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
const int maxn = 50000 + 10, maxm = 100000 + 10, inf = 1e9;

int m, n, k;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

inline void init()
{
	REP(i, 1, e) bg[i] = 0;
	e = 0;
}

int dfn[maxn], low[maxn], belong[maxn], stack[maxn], top, deep, cnt;
bool vis[maxn];

void tarjan(const int &x)
{
	dfn[x] = low[x] = ++deep;
	vis[x] = 1;
	stack[++top] = x;
	for (register int i = bg[x]; i ; i = ne[i])
		if (!dfn[to[i]])
		{
			tarjan(to[i]);
			chkmin(low[x], low[to[i]]);
		}
		else if (vis[to[i]]) chkmin(low[x], low[to[i]]);
	if (dfn[x] == low[x])
	{
		belong[x] = ++cnt;
		vis[x] = 0;
		while (stack[top] ^ x)
		{
			belong[stack[top]] = cnt;
			vis[stack[top--]] = 0;
		}
		top--;
	}

}

int nodein[maxn];

int main()
{
#ifdef CraZYali
	freopen("IntelligenceSystem.in", "r", stdin);
	freopen("IntelligenceSystem.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) != EOF)
	{
		while (m --> 0)
		{
			register int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x + 1, y + 1, z);
		}
		REP(i, 1, n) if (!dfn[i]) tarjan(i);
		REP(i, 0, cnt) nodein[i] = inf;
		REP(x, 1, n)
			for (register int i = bg[x]; i ; i = ne[i])
				if (belong[x] ^ belong[to[i]]) chkmin(nodein[belong[to[i]]], w[i]);
		register int ans = 0;
		REP(i, 1, cnt) ans += nodein[i] * (nodein[i] != nodein[0]);
		printf("%d\n", ans);
		e = cnt = deep = top = 0;
		REP(i, 1, n) bg[i] = dfn[i] = low[i] = vis[i] = 0;
	}
	
	return 0;
}
