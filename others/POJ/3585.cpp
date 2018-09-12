#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;
const int maxn = 2e5 + 10, maxm = maxn;

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

int dp[maxn], F[maxn], deg[maxn];

void dfs(int x, int fa = -1)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs(to[i], x);
			if (deg[to[i]] > 1) dp[x] += min(w[i], dp[to[i]]);
			else dp[x] += w[i];
		}
}

void get(int x, int fa = -1)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			if (deg[x] == 1) F[to[i]] = dp[to[i]] + w[i];
			else F[to[i]] = dp[to[i]] + min(w[i], F[x] - min(dp[to[i]], w[i]));
			get(to[i], x);
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
		e = 1;
		REP(i, 1, n) bg[i] = dp[i] = deg[i] = 0;
		REP(i, 2, n)
		{
			register int x(read<int>()), y(read<int>()), z(read<int>());
			deg[x]++;deg[y]++;
			add(x, y, z);
			add(y, x, z);
		}
		
		dfs(1);
		F[1] = dp[1];
		get(1);
		register int ans = F[1];
		REP(i, 2, n) chkmax(ans, F[i]);
		printf("%d\n", ans);
	}
	
	return 0;
}
