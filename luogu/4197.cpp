#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 1e5 + 10, maxm = 5e5 + 10, n_log_n = 3600000;

int bg[maxn << 1], to[maxm], ne[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int fa[maxn << 1];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m, q, cur, M;
int val[maxn << 1];
struct Edge
{
	int x, y, z;
	Edge() {}
	Edge(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
}E[maxm];
bool cmp(Edge A, Edge B) {return A.z < B.z;}

int N, grand[maxn << 1][25], LOG, Left[maxn << 1], Right[maxn << 1];
int dfn[maxn], dfs_clock, vv[maxn];

void prepare(int x)
{
	if (x <= n) vv[Left[x] = Right[x] = dfn[x] = ++dfs_clock] = val[x];
	bool flag = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			grand[to[i]][0] = x;
			prepare(to[i]);
			if (x > n)
				if (!flag) {Left[x] = Left[to[i]];Right[x] = Right[to[i]];flag = 1;}
				else
				{
					chkmin(Left[x], Left[to[i]]);
					chkmax(Right[x], Right[to[i]]);
				}
		}
}
void output(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			printf("%d %d\n", x, to[i] <= n&&0 ? dfn[to[i]] : to[i]);
			output(to[i]);
		}
}

int a[maxn], b[maxn];

int rt[n_log_n], ls[n_log_n], rs[n_log_n], sum[n_log_n], nd_cur;

#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

void build(int pre, int &p, int l, int r, int pos)
{
	p = ++nd_cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	sum[p] = sum[pre] + 1;
	if (l == r) return;
	if (pos <= mid) build(ls[pre], lson, pos);
	else build(rs[pre], rson, pos);
}

int query(int u, int v, int l, int r, int k)
{
	if (l >= r) return l;
	int x = sum[ls[v]] - sum[ls[u]];
	if (x < k) return query(rs[u], rs[v], mid + 1, r, k - x);
	else return query(ls[u], ls[v], l, mid, k);
}

int main()
{
#ifdef CraZYali
	file("4197");
#endif
	cin >> n >> m >> q;cur = n;
	REP(i, 1, n) scanf("%d", val + i);
	REP(i, 1, n * 2) fa[i] = i;
	REP(i, 1, m)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		E[i] = Edge(x, y, z);
	}
	sort(E + 1, E + 1 + m, cmp);
	int cnt = 0;
	REP(i, 1, m)
	{
		int x(find(E[i].x)), y(find(E[i].y));
		if (x ^ y)
		{
			val[++cur] = E[i].z;
			add(cur, x);
			add(cur, y);
			fa[x] = fa[y] = cur;
			if (++cnt == n - 1) break;
		}
	}
	N = n + n - 1;
	prepare(cur);
	LOG = log2(N);
	REP(j, 1, LOG)
		REP(i, 1, N)
		grand[i][j] = grand[grand[i][j-1]][j-1];
	//	REP(i, n+1, N)
	//		printf("%d %d %d\n", i, Left[i], Right[i]);
	//	output(cur);
	REP(i, 1, n) a[i] = b[i] = vv[i];
	//	al[dfn[i]];
	sort(b + 1, b + 1 + n);
	M = unique(b + 1, b + 1 + n) - b - 1;
	REP(i, 1, n) build(rt[i-1], rt[i], 1, M, lower_bound(b + 1, b + 1 + M, a[i]) - b);
	//	REP(i, 1, n) printf("%d%c", dfn[i], i == n ? '\n' : ' ' );
	//	REP(i, 1, n) printf("%d%c", vv[i], i == n ? '\n' : ' ' );
	//	REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	//	REP(i, 1, M) printf("%d%c", b[i], i == M ? '\n' : ' ' );
	//	REP(i, 1, n) printf("%d%c", lower_bound(b+1,b+1+M,a[i])-b, i == n ? '\n' : ' ' );
	//	REP(i, 1, n)
	//		REP(j, i, n)
	//		REP(k, 1, j - i + 1)
	//		printf("%d %d %d %d\n", i, j, k, b[query(T[i-1], T[j], 1, M, k)]);
	while (q--)
	{
		int v, x, k;
		scanf("%d%d%d", &v, &x, &k);
		//		cout << v << " -> ";
		DREP(i, LOG, 0)
			if (!grand[v][i]) continue;
			else if (val[grand[v][i]] <= x) v = grand[v][i];
		//		cout << v << "\n";
		//		cout << Left[v] << ' ' << Right[v] << endl;
		int len = Right[v] - Left[v] + 1;
		printf("%d\n", k > len ? - 1 : b[query(rt[Left[v]-1], rt[Right[v]], 1, M, len - k + 1)]);
	}
	return 0;
}
