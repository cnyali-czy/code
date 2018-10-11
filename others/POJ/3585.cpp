#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200000 + 10, maxm = maxn, inf = 1e9;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> T read()
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

int m, n, k;

int D[maxn], F[maxn];
int deg[maxn];

void dfs(int x, int fa)
{
	D[x] = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs(to[i], x);
			if (deg[to[i]] > 1) D[x] += min(D[to[i]], w[i]);
			else D[x] += w[i];
		}
}

void dp(int x, int fa)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dp(to[i], x);
			if (deg[x] == 1) F[to[i]] = D[to[i]] + w[i];
			else F[to[i]] = D[to[i]] + min(F[x] - min(D[to[i]], w[i]), w[i]);
		}
}

int main()
{
#ifdef CraZYali
	freopen("3585.in", "r", stdin);
	freopen("3585.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();
		REP(i, 1, n) bg[i] = deg[i] = 0;
		e = 1;

		REP(i, 2, n)
		{
			register int x = read<int>(), y = read<int>(), z = read<int>();
			deg[x]++;deg[y]++;
			add(x, y, z);add(y, x, z);
		}
		dfs(1, 0);

		F[1] = D[1];
		dp(1, 0);

		register int ans = F[1];
		REP(i, 2, n) chkmax(ans, F[i]);
		printf("%d\n", ans);
	}

	return 0;
}
