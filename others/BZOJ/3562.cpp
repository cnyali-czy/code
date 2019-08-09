#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <bitset>
#include <vector>

using namespace std;
const int maxn = 5000 + 10, maxm = 200000 + 10, maxq = 100000 + 10;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, q, N;
int x[maxm + maxq], y[maxm + maxq], z[maxm + maxq];

int fa[maxn];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}
int id[maxn], cur;

int belong[maxn], ans, dfn;

int have[maxn][maxn], G[maxn][maxn];
int bg[maxn], ne[maxm + maxq << 1], to[maxm + maxq << 1], e;
void dfs(int x, int y)
{
	belong[x] = y;
	for (int i = bg[x]; i ; i = ne[i]) if (G[x][to[i]]&&belong[to[i]]!=y)dfs(to[i], y);
}
void Add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

void add(int x, int y)
{
	if (belong[x] ^ belong[y])
	{
		--ans;
		dfs(y, belong[x]);
	}
	G[x][y]++, G[y][x]++;
	if(!have[x][y]) Add(x, y), Add(y, x), have[x][y] = have[y][x]=1;
}
void del(int x, int y)
{
	G[x][y]--, G[y][x]--;
	dfs(x, ++dfn);
	if (belong[x] ^ belong[y]) ans++;
}

int main()
{
#ifdef CraZYali
	freopen("3562.in", "r", stdin);
	freopen("3562.out", "w", stdout);
#endif
	cin >> n >> m ;
	REP(i, 1, n) fa[i] = i;

	REP(i, 1, m)
	{
		x[i] = read<int>(), y[i] = read<int>();
		G[x[i]][y[i]] ++, G[y[i]][x[i]]++;
	}

	cin >> q;
	REP(i, m + 1, m + q)
	{
		char c = getchar();
		while (!isalpha(c)) c = getchar();
		if (c == 'Q') z[i] = 1;
		else
		{
			x[i] = read<int>();y[i] = read<int>();
			if (c == 'D') z[i] = 2, G[x[i]][y[i]] = G[y[i]][x[i]] = 0;
			else z[i] = 3;
		}
	}
	REP(i, 1, m) if (G[x[i]][y[i]]) uni(x[i], y[i]);
	REP(i, 1, n) if (i == find(i)) id[i] = ++cur;
	REP(i, 1, m + q) if (x[i]+y[i])
	{
		x[i] = id[find(x[i])];
		y[i] = id[find(y[i])];
	}
	n = dfn = ans = cur;
	REP(i, 1, cur) belong[i] = i;
	REP(i, 1, n) REP(j, 1, n) G[i][j] = 0;
	REP(i, 1, m) if (x[i] ^ y[i]) add(x[i], y[i]);
	REP(i, m + 1, m + q)
		if (z[i] == 1) printf("%d\n", ans);
		else if (x[i] ^ y[i])
			if(z[i] == 2) del(x[i], y[i]);
			else add(x[i], y[i]);
	return 0;
}
