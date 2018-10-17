#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;
const int maxn = 1e3 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
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

int m, n, k, LOG, ans;

int grand[maxn][11], depth[maxn];

void dfs(int x, int fa)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			dfs(to[i], x);
		}
}

int getlca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0)
		if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	else
	{
		DREP(i, LOG, 0)
			if (grand[x][i] ^ grand[y][i])
			{
				x = grand[x][i];
				y = grand[y][i];
			}
		return grand[x][0];
	}
}

set <int> S;
set <int> :: iterator it;

bool toolow(int x)
{
	it = S.lower_bound(x - k);
	if (it != S.end() && abs(x - *it) <= k) return 1;
	it = S.lower_bound(x);
	if (it != S.end() && abs(x - *it) <= k) return 1;
	return 0;
}

signed main()
{
#ifdef CraZYali
	freopen("T50760.in", "r", stdin);
	freopen("T50760.out", "w", stdout);
#endif
	cin >> n >> k;
	if (k == 0) {cout << n + n * (n - 1) / 2;return 0;}
	register bool flag = 1;
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		flag &= (abs(x - y) == 1);
		add(x, y);add(y, x);
	}
	if (flag) {cout << n;return 0;}

	LOG = log2(n);
	depth[1] = 1;
	dfs(1, 0);

	REP(j, 1, LOG)
		REP(i, 1, n) grand[i][j] = grand[grand[i][j-1]][j-1];

	REP(i, 1, n)
		REP(j, i + 1, n)
		{
			int lca = getlca(i, j);
			register int x = i, y = j;
			S.clear();
			while (x ^ lca)
			{
				if (toolow(x)) goto ne;
				S.insert(x);
				x = grand[x][0];
			}
			while (y ^ lca)
			{
				if (toolow(y)) goto ne;
				S.insert(y);
				y = grand[y][0];
			}
			if (toolow(lca)) goto ne;
			ans++;
ne:;
		}
	cout << n + ans;
	return 0;
}
