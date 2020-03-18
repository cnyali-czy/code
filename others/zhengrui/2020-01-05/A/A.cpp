/*
	Problem:	A.cpp
	Time:		2020-02-21 11:58
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5;

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

namespace run
{
	const int MOD = 1e9 + 7;
	typedef long long i64;
	inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
	inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
	inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
	inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
	int dp[maxn][maxn], a[maxn], b[maxn], n, m;
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
	int solve(int l, int r)
	{
		REP(i, 0, n) REP(j, 0, n) dp[i][j] = 0;
		dp[0][0] = 1;
		int L = m, R = n;
		REP(i, 0, n-1) REP(j, 0, i) if (dp[i][j])
		{
			while (R > m && b[i] + a[R-1] <= r) --R;
			inc(dp[i+1][j+1], mul(dp[i][j], sub(n, add(R, j))));
			while (L > 0 && b[i] + a[L-1] <  l) --L;
			inc(dp[i+1][j], mul(dp[i][j], L - (m - (i + 1 - j))));
		}
		return dp[n][n - m];
	}
	int main()
	{
		n = read<int>();m = read<int>();
		REP(i, 0, n-1) a[i] = read<int>();
		REP(i, 0, n-1) b[i] = read<int>();
		sort(a + 0, a + 0 + n, greater <int> ());
		sort(b + 0, b + 0 + n, greater <int> ());
		int ans = 0;
		REP(T, 0, 2000)
			inc(ans, sub(solve(T, T), solve(T + 1, T)));
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	return run::main();
}
