#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int maxn = 1000 + 10, maxm = 1000 + 10;

int n, m, k;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int dis[maxn];
int v[maxn], ccc;

bool del[maxn];

void getdis(int x, int fa = -1)
{
	v[++ccc] = dis[x];
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !del[to[i]])
		{
			dis[to[i]] = dis[x] + w[i];
			getdis(to[i], x);
		}
}

int sum[maxn], allnode;
int Min;

int getroot(int x, int fa = -1)
{
	sum[x] = 1;
	register int Max = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !del[to[i]])
		{
			getroot(to[i], x);
			sum[x] += sum[to[i]];
			chkmax(Max, sum[to[i]]);
		}
	register int temp = max(Max, allnode - Max);
	if (temp < Min)
	{
		Min = temp;
		return x;
	}
	else return -1;
}

int Getroot(int x, int all = n)
{
	allnode = all;
	Min = (((1 << 30) - 1) << 1) + 1;
	return getroot(x);
}

int ans;

int calc(int x, int now = 0)
{
	ccc = 0;
	dis[x] = now;
	getdis(x);
	sort(v + 1, v + ccc + 1);
	register int l(1), r(ccc), tot(0);

	while (l < r)
		if (v[l] + v[r] <= k) tot += r - l++;
		else r--;
	return tot;
}

void solve(int x, int fa = -1)
{
	del[x] = 1;
	ans += calc(x);
	for (register int i = bg[x]; i ; i = ne[i])
		if (!del[to[i]] && to[i] ^ fa)
		{
			ans -= calc(to[i], w[i]);
			solve(Getroot(to[i], sum[x]), x);
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
		e = 1;
		REP(i, 1, n) del[i] = bg[i] = 0;
		REP(i, 2, n)
		{
			register int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z);add(y, x, z);
		}
		ans = 0;
		solve(Getroot(1));
		printf("%d\n", ans);
	}
	
	return 0;
}
