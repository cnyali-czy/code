#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 10000 + 10, maxm = 10000 + 10;
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
bool vis[maxn];

int sum[maxn], Max[maxn], allnode, hvy;
void get(int x, int fa = -1)
{
	sum[x] = 1;Max[x] = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			get(to[i], x);
			sum[x] += sum[to[i]];
			chkmax(Max[x], sum[to[i]]);
		}
	chkmax(Max[x], allnode - Max[x]);
	if (Max[x] < Max[hvy] || !hvy) hvy = x;
}

int depth[maxn], d[maxn];
void get_depth(int x, int fa = -1)
{
	d[++d[0]] = depth[x];
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			depth[to[i]] = depth[x] + w[i];
			get_depth(to[i], x);
		}
}

int get_sum(int x, int thisw = 0)
{
	depth[x] = thisw;d[0] = 0 ;
	get_depth(x);
	sort(d + 1, d + 1 + d[0]);
	int l = 1, r= d[0], res = 0;
	while (l <= d[0])
	{
		while (r > l && d[r] + d[l] > k) r--;
		res += max(0, r - l);
		l++;
	}
	return res;
}

int ans;
void calc(int x)
{
	vis[x] = 1;
	ans += get_sum(x);
	for (register int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]])
		{
			ans -= get_sum(to[i], w[i]);
			hvy = 0;allnode = sum[to[i]];
			get(to[i]);
			calc(hvy);
		}
}

int main()
{
#ifdef CraZYali
	freopen("1741.in", "r", stdin);
	freopen("1741.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &k) * (n + k))
	{
		e = 1;REP(i, 1, n) bg[i] = vis[i] = 0;
		REP(i, 2, n)
		{
			register int x = read<int>(), y = read<int>(), z = read<int>();
			add(x, y, z);add(y, x, z);
		}
		ans = 0;
		calc(1);
		printf("%d\n", ans);
	}
		
	return 0;
}
