#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100 + 5, maxm = 1000 + 10, MOD = 31011;

struct edge
{
	int x, y, z;
	edge(){}
	edge(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
}E[maxm];
bool cmp(edge A, edge B) {return A.z < B.z;}

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

int n, m, tot;

int fa[maxn];
int find(int x) {return fa[x] == x ? x : find(fa[x]);}

struct data
{
	int l, r, v;
	data() : v(0) {}
}a[maxm];
int cnt;

int ret, ans = 1;
void dfs(int x, int now, int k)
{
	if (now == a[x].r) {ret += k == a[x].v;return;}
	now++;
	int u(find(E[now].x)), v(find(E[now].y));
	if (u ^ v)
	{
		fa[u] = v;
		dfs(x, now, k + 1);
		fa[u] = u;fa[v] = v;
	}
	dfs(x, now, k);
}

int main()
{
#ifdef CraZYali
	freopen("1016.in", "r", stdin);
	freopen("1016.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, m)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		E[i] = edge(x, y, z);
	}
	sort(E + 1, E + 1 + m, cmp);
	REP(i, 1, m)
	{
		if (E[i].z ^ E[i-1].z) a[cnt].r = i - 1, a[++cnt].l = i;
		int x(E[i].x), y(E[i].y);
		if (find(x) ^ find(y))
		{
			fa[find(x)] = find(y);
			a[cnt].v++;
			tot++;
		}
	}
	a[cnt].r = m;
	if (tot != n - 1) {putchar('0');return 0;}
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, cnt)
	{
		ret = 0;
		dfs(i, a[i].l-1, 0);
		(ans *= ret) %= MOD;
		REP(j, a[i].l, a[i].r) fa[find(E[j].x)] = find(E[j].y);
	}
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
