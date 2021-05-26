#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 5000 + 10, MOD = 1e9 + 7; 

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int n, a[maxn]; 

int g[maxn], dp[maxn][maxn], siz[maxn]; 

int t[maxn];
void dfs(int x, int fa = -1)
{
	dp[x][1] = 1;
	siz[x] = 1;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs(to[i], x);
			REP(j, 0, siz[x])
				REP(k, 0, siz[to[i]])
					(t[j + k] += dp[x][j] * dp[to[i]][k] % MOD) %= MOD; 
			siz[x] += siz[to[i]];
			REP(j, 0, siz[x]) dp[x][j] = t[j], t[j] = 0;
		}
	int &sum = dp[x][0];
	sum = 0;
	REP(i, 0, siz[x]) sum += -dp[x][i] * g[i] % MOD, i++;
	sum %= MOD;
}

signed main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		add(x, y);add(y, x);
	}
	g[0] = 1; 
	REP(i, 2, n) g[i] = g[i-2] * (i-1) % MOD, i++;
	dfs(1);  
	cout << (-dp[1][0] % MOD + MOD) % MOD << endl;
	return 0; 
} 
