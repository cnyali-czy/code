#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20000 + 10, maxm = 1e5 + 10;

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
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k;
int cut[maxn], cnt;

int dfn[maxn], low[maxn], dfs_clock;
bool iscut[maxn];

void dfs(int u, int fa = -1)
{
	dfn[u] = low[u] = ++dfs_clock;
	int child = 0;
	for (register int i = bg[u]; i ; i = ne[i])
		if (!dfn[to[i]])
		{
			child++;
			dfs(to[i], u);
			chkmin(low[u], dfn[to[i]]);
			if (low[to[i]] <= dfn[u]) iscut[u] = 1;
		}
		else if (to[i] ^ fa) chkmin(low[u], low[to[i]]);
	if (fa == -1 && child < 2) iscut[u] = 0;
}

int main()
{
#ifdef CraZYali
	freopen("3388-new.in", "r", stdin);
	freopen("3388-new.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	REP(i, 1, n) if (!dfn[i]) dfs(i);
	REP(i, 1, n) if (iscut[i]) cut[++cnt] = i;
	printf("%d\n", cnt);
	REP(i, 1, cnt) printf("%d\n", cut[i]);
	return 0;
}
