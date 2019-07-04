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
const int maxn = 40000 + 10, maxm = maxn;
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

int n, k;
bool vis[maxn];
int siz[maxn], Max[maxn], root, allnode;
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
int calc(int x, int ddd)
{
	depth[x] = ddd;
	cnt = 0;
	getdepth(x);
	int res(0);
	int l = 1, r = cnt;
	sort(d + 1, d + 1 + cnt);
	while (l < r)
		if (d[l] + d[r] <= k) res += r - l++;
		else r--;
	return res;
}
int ans;
void solve(int x, int fa = -1)
{
	vis[x] = 1;
	ans += calc(x, 0);
	for (int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]] && to[i] ^ fa)
		{
			ans -= calc(to[i], w[i]);
			allnode = siz[to[i]];
			root = 0;
			getroot(to[i]);
			solve(root);
		}
}

int main()
{
#ifdef CraZYali
	file("4178");
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	cin >> k;
	allnode = n;
	Max[0] = 1e9;
	getroot(1);
	solve(root);
	cout << ans << endl;
	return 0;
}
