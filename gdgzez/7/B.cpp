/*
	Problem:	B.cpp
	Time:		2020-03-25 15:04
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
#define i64 long long
using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

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

int dp[maxn], f[18], n, m;

void init()
{
	REP(i, 1, m) dp[i] = 1;
	f[1] = m;
	REP(i, 2, 17)
	{
		memset(dp, 0, 1 << i);
		DEP(j, m, 1 << i - 2) if (dp[j])
		{
            if(!dp[j]) continue;
			REP(k, 2, m / j) inc(dp[k * j], dp[j]);
			dp[j] = 0;
        }
		int &res = f[i];
		REP(j, 1 << i - 2, m) inc(res, dp[j]);
    }
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	init();
	REP(i, 1, n) dp[i] = 0;
    dp[0] = n & 1 ? -1 : 1;
	REP(i, 1, n) REP(j, 1, min(i, 17))
		dec(dp[i], mul(f[j], dp[i - j]));
	cout << dp[n] << endl;
    return 0;
}
