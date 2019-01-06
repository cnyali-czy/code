#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 300000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int n, a[maxn];
int depth[maxn], grand[maxn][20], LOG;

void dfs(int x)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			dfs(to[i]);
		}
}

int getlca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0)
		if (depth[grand[x][i]] >= depth[y]) x = grand[x][i] ;
	if (x == y) return x;
	else
	{
		DREP(i, LOG, 0) if (grand[x][i] ^ grand[y][i]) x = grand[x][i], y = grand[y][i];
		return grand[x][0];
	}
}

int cnt[maxn];

int calc(int x, int fa = -1)
{
	for (register int i = bg[x];  i ; i = ne[i])
		if (to[i] ^ fa)
		{
			calc(to[i], x);
			cnt[x] += cnt[to[i]];
		}
}

int main()
{
#ifdef CraZYali
	freopen("3258.in", "r", stdin);
	freopen("3258.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	depth[1] = 1;
	dfs(1);
	LOG = log2(n);
	REP(j, 1, LOG)
		REP(i, 1, n) grand[i][j] = grand[grand[i][j-1]][j-1];
	REP(i, 2, n) cnt[a[i]]++, cnt[a[i-1]]++, cnt[getlca(a[i], a[i-1])]--, cnt[grand[getlca(a[i], a[i-1])][0]]--;
	calc(1);
	REP(i, 2, n) cnt[a[i]]--;
	REP(i, 1, n) printf("%d\n", cnt[i]);

	return 0;
}
