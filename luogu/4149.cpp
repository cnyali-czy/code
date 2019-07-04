#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 200000 + 10, maxm = maxn, inf = 1e9;
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

int n, k, allnode, ans = inf;

bool vis[maxn];
int siz[maxn], Max[maxn], root;
void getroot(int x, int fa = -1)
{
	siz[x] = 1;	Max[x] = 0;
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

int depth[maxn], len[maxn], cnt;
pair <int, int> d[maxn];
void getdepth(int x, int fa = -1)
{
	d[++cnt] = make_pair(depth[x], x);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa && !vis[to[i]])
		{
			len[to[i]] = len[x] + 1;
			depth[to[i]] = depth[x] + w[i];
			getdepth(to[i], x);
		}
}

int p[maxn];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first;}
void calc(int x, int dd = 0)
{
	cnt = 0;
	len[x] = (dd > 0);
	depth[x] = dd;
	getdepth(x);
	sort(d + 1, d + 1 + cnt, cmp);
	int l = 1, r = cnt, o = dd ? -1 : 1;
	while (l < r)
	{
		while (r > l && d[l].first + d[r].first > k) r--;
		if (r > l && d[l].first + d[r].first == k)
		{
			int R = r;
			while (R > l && d[l].first + d[R].first == k)
				p[len[d[l].second] + len[d[R--].second]] += o;
		}
		l++;
	}	
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
			getroot(to[i]);
			solve(root);
		}
}

int main()
{
#ifdef CraZYali
	file("4149");
#endif
	cin >> n >> k;
	REP(i, 2, n)
	{
		int x(read<int>() + 1), y(read<int>() + 1), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	allnode = n;
	Max[0] = inf;
	getroot(1);
	solve(root);
//	REP(i, 1, n) assert(p[i] < 0);
	REP(i, 1, n)
		if (p[i])
		{
			cout << i << endl;
			return 0;
		}
	cout << -1 << endl;
	return 0;
}
