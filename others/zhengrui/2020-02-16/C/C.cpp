/*
	Problem:	C.cpp
	Time:		2020-02-17 20:27
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
#define i64 long long
using namespace std;
const int maxn = 5000 + 10, MOD = 998244353, inv2 = MOD + 1 >> 1;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
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

int n, a[maxn], ans, dp[maxn];

void add0(int x)
{
	DEP(i, x, 1) inc(dp[i], mul(dp[i-1], i - (i > 1)));
}
void add1(int x)
{
	inc(ans, dp[1]);
	REP(i, 1, x) inc(dp[i], mul(dp[i+1], i + 1));
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n) inc(ans, MOD - (a[i] = read<int>()));
	sort(a + 1, a + 1 + n);dp[0] = 1;
	REP(i, 1, n)
	{
		REP(j, a[i - 1] + 1, a[i]) add0(j);
		add1(a[i]);
	}
	cout << mul(ans, inv2) << endl;
	return 0;
}
