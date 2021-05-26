#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define int long long

inline int read() {int x;scanf("%lld", &x);return x;}

using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int n, f[maxn], a[maxn], d[maxn];

void dfs(int x, int fa = 0)
{
	if (!ne[bg[x]])
	{
		f[x] = a[x];
		return;
	}
	int s = 0, mx = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		s += f[to[i]];
		mx = max(mx, f[to[i]]);
	}
	int Y = s - a[x], X = 2 * a[x] - s;
	if (Y < 0 || X < 0 || mx > a[x]) {puts("NO");exit(0);}
	f[x] = X;
}

signed main()
{
#ifdef CraZYali
	freopen("2304.in", "r", stdin);
	freopen("2304.out", "w", stdout);
#endif
	n = read();
	REP(i, 1, n) a[i] = read();
	REP(i, 2, n)
	{
		int x = read(), y = read();
		d[x]++;d[y]++;
		add(x, y);add(y, x);
	}
	if (n == 2)
	{
		puts(a[1] == a[2] ? "YES" : "NO");
		return 0;
	}
	REP(i, 1, n) if (d[i] > 1)
	{
		dfs(i);
		puts(f[i] ? "NO" : "YES");
		return 0;
	}
	return 0;
}
