#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int MOD = 998244353, maxn = 5000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void Add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}
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
#define i64 long long
int power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
int fac[maxn], Inv[maxn];
struct __init__
{
	__init__(const int n = maxn - 10)
	{
		fac[0] = 1;
		REP(i, 1, n) fac[i] = 1ll * fac[i-1] * i % MOD;
		Inv[n] = inv(fac[n]);
		DEP(i, n - 1, 0) Inv[i] = Inv[i + 1] * (i + 1ll) % MOD;
	}
}__INIT__;
inline int A(int n, int m) {cerr<<n<<' '<<m<<endl;return 1ll * fac[n] * Inv[n - m] % MOD;}
inline int C(int n, int m) {return 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
char s[maxn];

int lca[maxn][maxn];
int f[maxn];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}
bool vis[maxn];
void tarjan(int x, int fa = 0)
{
	f[x] = x;
	vis[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		tarjan(to[i], x);
		f[to[i]] = x;
	}
	REP(y, 1, n) if (vis[y]) lca[x][y] = lca[y][x] = find(y);
}
int F[maxn];

int dp[1 << 20][25];

int main()
{
	file("match");
	cin >> n;int m = n / 2;
	scanf("%s", s + 1);
	REP(i, 1, n) s[i] -= '0';
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		Add(x, y);Add(y, x);
	}
	REP(i, 1, n) lca[i][i] = i;
	tarjan(1);
	const int lim = (1 << n) - 1;
	dp[0][0] = 1;
	REP(S, 0, lim)
	{
		REP(k, 0, m) if (dp[S][k])
		REP(x, 1, n) if (!(S & (1 << x - 1)))
			REP(y, 1, n) if (!(S & (1 << y - 1)))
			if (s[x] != s[y] && (lca[x][y] == x || lca[x][y] == y))
				(dp[S | (1 << x - 1) | (1 << y - 1)][k + 1] += dp[S][k]) %= MOD;
			else
				(dp[S | (1 << x - 1) | (1 << y - 1)][k] += dp[S][k]) %= MOD;
	}
	REP(i, 0, m) printf("%d%c", dp[lim][i], i == m ? '\n' : ' ' );
	return 0;
}
