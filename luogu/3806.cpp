#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

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

int son[maxn], Max[maxn], allnode, hvy;
bool vis[maxn];

void gethvy(int x, int fa = -1)
{
	son[x] = 1;Max[x] = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			gethvy(to[i], x);
			son[x] += son[to[i]];
			chkmax(Max[x], son[to[i]]);
		}
	chkmax(Max[x], allnode - Max[x]);
	if (!hvy || Max[x] < Max[hvy]) hvy = x;
}

int depth[maxn], d[maxn], tot;

void get_depth(int x, int fa = -1)
{
	d[++tot] = depth[x];
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			depth[to[i]] = depth[x] + w[i];
			get_depth(to[i], x);
		}
}
int get_sum(int x, int y)
{
	tot = 0;
	depth[x] = y;
	get_depth(x);
	sort(d + 1, d + 1 + tot);
	int res1 = 0, res2 = 0, l = 1, r = tot;

	while (l <= r)
		if (d[l] + d[r] <= k) res1 += r - l++;
		else r--;
	l = 1, r = tot;
	while (l <= r)
		if (d[l] + d[r] >= k) res2 += r-- - l;
		else l++;
	return res1 + res2 - tot * (tot - 1) / 2;
}

int ans;
int calc(int x)
{
	vis[x] = 1;
	ans += get_sum(x, 0);
	for (register int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]])
		{
			ans -= get_sum(to[i], w[i]);
			allnode = son[to[i]];hvy = 0;
			gethvy(to[i]);
			calc(hvy);
		}
}

int main()
{
#ifdef CraZYali
	freopen("3806.in", "r", stdin);
	freopen("3806.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}

	while (m --> 0)
	{
		REP(i, 1, n) vis[i] = 0;
		k = read<int>();
		allnode = n;hvy = 0;
		gethvy(1);
		ans = 0;
		calc(hvy);
		if (ans) printf("AYE\n");
		else printf("NAY\n");
	}
	return 0;
}
