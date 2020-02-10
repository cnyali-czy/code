/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.07 23:31
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 10, MOD = 1e9 + 7;

vector <int> G[maxn];
void add_edge(int x, int y)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}

int add(int x, int y)
{
	int res = x + y;
	if (res >= MOD) return res - MOD;
	return res;
}
void inc(int &x, int y)
{
	x += y;
	if (x >= MOD) x -= MOD;
}
int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) return res + MOD;
	return res;
}
int mul(int x, int y)
{
	long long res = (long long)x * y;
	if (res >= MOD) return res % MOD;
	return res;
}
int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int fac[maxn], Inv[maxn];
struct __init__
{
	__init__(const int n = maxn - 10)
	{
		fac[0] = 1;
		REP(i, 1, n) fac[i] = mul(fac[i-1], i);
		Inv[n] = inv(fac[n]);
		DEP(i, n - 1, 0) Inv[i] = mul(Inv[i + 1], i + 1);
	}
}__INIT__;
inline int C(int n, int m) {return n < m ? 0 : mul(fac[n], mul(Inv[m], Inv[n - m]));}

int n, dp[maxn][maxn], siz[maxn];

void dfs(int u, int fa = 0)
{
	dp[u][1] = siz[u] = 1;
	for (int v : G[u]) if (v ^ fa)
	{
		dfs(v, u);
		DEP(i, siz[u] + siz[v], 1)
		{
			dp[u][i] = mul(dp[u][i], dp[v][0]);
			DEP(j, min(i - 1, siz[u]), max(1, i - siz[v]))
				inc(dp[u][i], mul(C(i - 1, j - 1), mul(dp[v][i - j], dp[u][j])));
		}
		siz[u] += siz[v];
	}
	DEP(i, siz[u], 0) inc(dp[u][i], dp[u][i+1]);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 2, n) add_edge(read<int>(), read<int>());
	dfs(1);
	cout << dp[1][0] << endl;
	return 0;
}
