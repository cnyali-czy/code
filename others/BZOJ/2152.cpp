#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20000 + 10, maxm = maxn;

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

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
int m, n, k;

bool vis[maxn];

int sum[maxn], Max[maxn], hvy, allnode;
void gethvy(int x, int fa = -1)
{
	sum[x] = 1;Max[x] = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]] && to[i] ^ fa)
		{
			gethvy(to[i], x);
			sum[x] += sum[to[i]];
			chkmax(Max[x], sum[to[i]]);
		}
	chkmax(Max[x], allnode - Max[x]);
	if (hvy == 0 || Max[x] < Max[hvy]) hvy = x;
}

int depth[maxn], d[5];
void getdepth(int x, int fa = -1)
{
	d[depth[x]]++;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			depth[to[i]] = (depth[x] + w[i]) % 3;
			getdepth(to[i], x);
		}
}

int getsum(int x, int y)
{
	d[0] = d[1] = d[2] = 0;
	depth[x] = y % 3;getdepth(x);
	return d[0] * d[0] + d[1] * d[2] * 2;
}

int ans;
void calc(int x)
{
	vis[x] = 1;ans += getsum(x, 0);
	for (register int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]])
		{
			ans -= getsum(to[i], w[i]);
			hvy = 0;allnode = sum[to[i]];
			gethvy(to[i]);
			calc(hvy);
		}
}

int main()
{
#ifdef CraZYali
	freopen("2152.in", "r", stdin);
	freopen("2152.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}

	allnode = n;
	gethvy(1);
	calc(hvy);

	int g = gcd(ans, n * n);
	cout << ans / g << '/' << n * n / g;

	return 0;
}
