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
#define int long long

using namespace std;
const int maxn = 100000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
bool vis[maxn];
int c[maxn], cnt;

int siz[maxn], del[maxn], gx[maxn];
void dfs(int x, int fa = 0)
{
	int temp = del[c[fa]];
	siz[x] = 1;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs(to[i], x);
			siz[x] += siz[to[i]];
		}
	del[c[x]]++;
	if (fa)
	{
		gx[x] = siz[x] - del[c[fa]] + temp;
		del[c[fa]] += gx[x];
	}
}
int t, ans[maxn], b[maxn];

void get(int x, int fa = 0)
{
	int last = b[c[fa]];
	t += gx[x] - last;
	b[c[fa]] = gx[x];
	ans[x] = n * cnt - t + b[c[x]];
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa) get(to[i], x);
	b[c[fa]] = last;
	t -= gx[x] - b[c[fa]];
}

signed main()
{
#ifdef CraZYali
	file("2664");
#endif
	cin >> n;
	REP(i, 1, n)
	{
		c[i] = read<int>();
		if (!vis[c[i]]) cnt += ++vis[c[i]];
	}
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	dfs(1);
	REP(i, 1, 100000)
		if (vis[i]) t += (b[i] = n - del[i]);
	get(1);
	REP(i, 1, n) printf("%lld\n", ans[i]);
	return 0;
}
