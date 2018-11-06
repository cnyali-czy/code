#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>

using namespace std;
const int maxn = 25 , maxm = maxn * (maxn - 1) / 2;

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;
map <string, int> id;
int u[maxm], v[maxm], _w[maxm];

int g[maxn][maxn], l[maxn][maxn];

struct Edge
{
	int x, y, z;
	Edge() {};
	Edge(int _x, int _y, int _z) : x(_x), y(_y), z(_z){} 
	bool operator < (Edge B) const {return z < B.z;}
}E[maxm];int e;

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}

int ans, dp[maxn], U[maxn], V[maxn];
void dfs(int x, int fa)
{
	REP(i, 1, n)
		if (i ^ fa && g[x][i])
		{
			if (dp[i] != -1)
				if (dp[x] == -1 || dp[x] < l[x][i]) dp[i] = l[x][i], U[i] = x, V[i] = i;
				else dp[i] = dp[x], U[i] = U[x], V[i] = V[x];
			dfs(i, x);
		}
}
int a[maxn], pre[maxn];
bool pd[maxn];

int main()
{
#ifdef CraZYali
	freopen("1639.in", "r", stdin);
	freopen("1639.out", "w", stdout);
#endif
	memset(l, -1, sizeof(l));
	id["Park"] = n = 1;
	m = read<int>();
	REP(i, 1, m)
	{
		string a, b;
		cin >> a >> b >> _w[i];
		if (!id[a]) id[a] = ++n;
		if (!id[b]) id[b] = ++n;
		u[i] = id[a];v[i] = id[b];
		l[u[i]][v[i]] = l[v[i]][u[i]] = _w[i];
	}
	k = read<int>();
	REP(i, 1, m)
		if (u[i] ^ 1 && v[i] ^ 1) E[++e] = Edge(u[i], v[i], _w[i]);
	sort(E + 1 , E + 1 + e);
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, e)
		if (find(E[i].x) ^ find(E[i].y))
		{
			g[E[i].x][E[i].y] = g[E[i].y][E[i].x] = 1;
			uni(E[i].x, E[i].y);
			ans += E[i].z;
		}
	REP(i, 1, n) a[i] = 1e8;
	REP(i, 1, n)
		if (l[1][i] != -1)
		{
			int root = find(i);
			if (a[root] > l[1][i]) a[root] = l[1][i], pre[root] = i;
		}
	int nowk = 0;
	REP(i, 1, n)
		if (pre[i])
		{
			g[1][pre[i]] = g[pre[i]][1] = 1;
			ans += l[1][pre[i]];++nowk;
		}
	REP(i, nowk + 1, k)
	{
		REP(j, 1, n)
			if (g[1][j]) dp[j] = -1; else dp[j] = 0;
		dfs(1, 0);int mx = 0, bj;
		REP(j, 1, n)
			if (l[1][j] == -1 || g[1][j]) continue;
			else if (l[1][j] - dp[j] < mx) mx = l[1][j] - dp[j], bj = j;
		if (mx >= 0) break;
		else
		{
			ans += mx; g[U[bj]][V[bj]] = g[V[bj]][U[bj]] = 0;
			g[1][bj] = g[bj][1] = 1;
		}
	}
	printf("Total miles driven: %d", ans);
	return 0;
}
