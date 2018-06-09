#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 6000 + 10, maxm = maxn;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, x, y;

bool vis[maxn];
int dp[maxn][2], v[maxn], fa[maxn];

inline void DP(int x)
{
	if (vis[x]) return;
	vis[x] = 1;

	register int A(0), B(max(0, v[x]));
	for (register int i = bg[x]; i ; i = ne[i])
	{
		DP(to[i]);
		A += max(dp[to[i]][0], dp[to[i]][1]);
		B += dp[to[i]][0];
	}
	chkmax(dp[x][0], A);
	chkmax(dp[x][1], B);
}

int main()
{
#ifdef CraZYali
	freopen("Anniversaryparty.in", "r", stdin);
	freopen("Anniversaryparty.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d", v + i);
	while (scanf("%d %d", &x, &y) * x * y)
	{
		fa[x] = y;
		add(y, x);
	}
	REP(i, 1, n)
		if (!fa[i])
		{
			DP(i);
			printf("%d\n", max(dp[i][1], dp[i][0]));
			return 0;
		}
}
