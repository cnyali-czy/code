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
const int maxn = 10000 + 10, maxm = 50000 + 10, maxq = 30000 + 10;
struct Graph
{
	int bg[maxn], ne[maxn << 1], to[maxn << 1], num[maxn << 1], e;
	inline void add(int x, int y, int _num = 0)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		num[e] = _num;
	}
}T, Q;
int m, n, q;

int f[maxn];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}

struct edeg
{
	int x, y, z;
}e[maxm];

edeg _edeg(int X, int Y, int Z)
{
	edeg temp ;
	temp.x = X;
	temp.y = Y;
	temp.z = Z;
	return temp;
}

inline bool cmp(edeg A, edeg B) {return A.z > B.z;}

bool NoSolution[maxq], vis[maxn];
int ans[maxn];

void dfs(int x)
{
	vis[x] = 1;
	for (register int i = T.bg[x]; i ; i = T.ne[i])
		if (!vis[T.to[i]])
		{
			dfs(T.to[i]);
			f[T.to[i]] = x;
		}
	for (register int i = Q.bg[x]; i ; i = Q.ne[i])
		if (vis[Q.to[i]]) ans[Q.num[i]] = find(Q.to[i]);
}
int main()
{
#ifdef CraZYali
	freopen("1967.in", "r", stdin);
	freopen("1967.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) f[i] = i;
	REP(i, 1, m)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		e[i] = _edeg(x, y, z);
	}
	sort (e + 1, e + 1 + m, cmp);
	REP(i, 1, m)
	{
		int fx = find(e[i].x);
		int fy = find(e[i].y);
		if (fx != fy)
		{
			f[fx] = fy;
			T.add(e[i].x, e[i].y);
			T.add(e[i].y, e[i].x);
		}
	}
	REP(i, 1, n) f[i] = i;
	REP(x, 1, n)
		for (register int i = T.bg[x]; i ; i = T.ne[i])
			if (x > T.to[i]) f[find(x)] = find(T.to[i]);
	cin >> q;
	REP(i, 1, q)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (find(x) == find(y))
		{
			Q.add(x, y, i);
			Q.add(y, x, i);
		}
		else NoSolution[i] = 1;
	}
	REP(i, 1, n) f[i] = i;
	dfs(1);
	REP(i, 1, q)
		if (NoSolution[i]) printf("-1\n");
		else printf("%d\n", ans[i]);
	return 0;
}
