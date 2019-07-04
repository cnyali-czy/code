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
const int maxn = 10000 + 10, maxm = maxn, inf = 1e9;
int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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
int p[10000000 + 5];

bool vis[maxn];
int siz[maxn], Max[maxn], allnode, root;
void getroot(int x, int fa = -1)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			getroot(to[i], x);
			siz[x] += siz[to[i]];
			chkmax(Max[x], siz[to[i]]);
		}
	chkmax(Max[x], allnode - siz[x]);
	if (Max[x] < Max[root]) root = x;
}

int depth[maxn], d[maxn], cnt;
void getdepth(int x, int fa = -1)
{
	d[++cnt] = depth[x];
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			depth[to[i]] = depth[x] + w[i];
			getdepth(to[i], x);
		}
}

void calc(int x, int dd = 0)
{
	depth[x] = dd;
	cnt = 0;
	getdepth(x);
	REP(i, 1, cnt)
		REP(j, i + 1, cnt)
		if (d[i] + d[j] <= 10000000) p[d[i] + d[j]] += (dd ? -1 : 1);
}

void solve(int x)
{
	vis[x] = 1;
	calc(x);
	for (int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]])
		{
			calc(to[i], w[i]);
			allnode = siz[to[i]];
			root = 0;
			getroot(to[i], x);
			solve(to[i]);
		}
}

int main()
{
#ifdef CraZYali
	file("3806-new");
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	allnode = n;
	Max[0] = inf;
	getroot(1);
	solve(root);
	while (m--) printf("%s\n", p[read<int>()] ? "AYE" : "NAY");
//	REP(i, 1, 1000)if(p[i])cout<<i<<endl;
	return 0;
}
