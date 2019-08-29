#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 4e5 + 10, maxm = maxn << 1;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
long long ans;
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

int n, q;

int fa[maxn], ch[maxn][2];
long long v[maxn], f[maxn], s[maxn], a[maxn];
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
#define get(p) (rs(fa[p]) == p)
#define notroot(p) (ls(fa[p]) == p || get(p))

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

inline void pushup(int x) {s[x] = s[ls(x)] + s[rs(x)] + v[x];}
inline void rotate(int x)
{
	int y(fa[x]), k(get(x));
	ch[y][k] = ch[x][k ^ 1];
	if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
	if (notroot(y)) ch[fa[y]][get(y)] = x;
	fa[x] = fa[y];
	fa[ch[x][k ^ 1] = y] = x;
	pushup(y);
}
inline void splay(int x)
{
	while (notroot(x))
	{
		int y(fa[x]);
		if (notroot(y)) rotate(get(x) == get(y) ? y : x);
		pushup(x);
		rotate(x);
	}
}
inline void access(int x, long long val)
{
	a[x] += val;
	for (int u(0); x; u = x, x = fa[x])
	{
		splay(x);
		int r(rs(x));
		v[x] += val;s[x] += val;
		long long sum(v[x] + s[r]);
		if (r && s[r] * 2 <= sum) v[x] += s[r], rs(x) = 0;
		if (u && s[u] * 2 >  sum) v[x] -= s[u], rs(x) = u;
		ans -= f[x];ans += f[x] = min(sum - 1, sum - max(a[x], s[rs(x)]) << 1);
		pushup(x);
	}
}
int hvy[maxn];
void dfs(int x, int pa = -1)
{
	s[x] = a[x];
	int &z = hvy[x];
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ pa)
		{
			fa[to[i]] = x;
			dfs(to[i], x);
			s[x] += s[to[i]];
			if (s[to[i]] > s[z]) z = to[i];
		}
	ans += f[x] = min(s[x] - 1, s[x] - max(a[x], s[z]) << 1);
}

signed main()
{
#ifdef CraZYali
	freopen("2434.in", "r", stdin);
	freopen("2434.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	dfs(1);
	cout << ans << endl;
	REP(i, 1, n)
	{
		v[i] = s[i];
		if (s[hvy[i]] * 2 > s[i]) v[i] -= s[rs(i) = hvy[i]];
	}
	while (q--)
	{
		int x(read<int>()), y(read<int>());
		access(x, y);
		printf("%lld\n", ans);
	}
	return 0;
}
