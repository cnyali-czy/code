/*
	Problem:	3864.cpp
	Time:		2020-03-09 20:03
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define int long long
#define i64 long long
using namespace std;
const int maxn = 20, maxm = 1000 + 10, maxs = (1 << 15) + 5;
#define MOD 1000000007
inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;
char s[maxn];

namespace run
{
	char DNA[] = {'A', 'T', 'G', 'C'};

	int go[maxs][4], dp[2][maxs], ans[maxn];
	int f[maxn], g[maxn];

	inline void init()
	{
		REP(i, 0, (1 << n) - 1)
		{
			memset(f, 0, sizeof f);memset(g, 0, sizeof g);
			REP(j, 1, n) f[j] = f[j - 1] + ((i >> j - 1) & 1);
			REP(k, 0, 3)
			{
				REP(j, 1, n)
				{
					g[j] = max(g[j - 1], f[j]);
					if (DNA[k] == s[j]) chkmax(g[j], f[j - 1] + 1);
				}
				go[i][k] = 0;
				REP(j, 0, n - 1) if (g[j + 1] - g[j]) go[i][k] |= (1 << j);
			}
		}
	}

	inline void solve()
	{
		init();
		memset(dp, 0, sizeof dp);
		dp[0][0] = 1;
		int cur = 0;
		REP(i, 1, m)
		{
			cur = !cur;
			memset(dp[cur], 0, sizeof dp[cur]);
			REP(j, 0, (1 << n) - 1) REP(k, 0, 3)
				inc(dp[cur][go[j][k]], dp[!cur][j]);
		}
		memset(ans, 0, sizeof ans);
		REP(i, 0, (1 << n) - 1)
			inc(ans[__builtin_popcount(i)], dp[m & 1][i]);
		REP(i, 0, n) cout << ans[i] << '\n';
	}
}

signed main()
{
#ifdef CraZYali
	file("3864");
#endif
	register int T = read<int>();
	while (T--)
	{
		scanf("%s", s + 1);n = strlen(s + 1);
		m = read<int>();
		run::solve();
	}
	return 0;
}
