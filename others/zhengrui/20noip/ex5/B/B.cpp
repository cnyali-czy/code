/*
	Problem:	B.cpp
	Time:		2020-12-18 20:03
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 3e5 + 10, MOD = 1e9 + 7;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], w[maxn], s[maxn], pre[maxn], suf[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) s[i] = (s[i - 1] + (w[i] = read<int>())) % MOD;
	REP(i, 1, n) pre[i] = (pre[i - 1] + s[i]) % MOD;
	DEP(i, n, 1) suf[i] = (suf[i + 1] + s[i]) % MOD;
	i64 ans = 0;
	REP(i, 1, n)
	{
		i64 res = 0;
		res = suf[n - i + 1] + MOD - pre[i - 1];
//		REP(j, 1, i) REP(k, 0, n - i) res += w[k + j];
		ans = (ans + res % MOD * a[i]) % MOD;
	}
	cout << ans << endl;
	return 0;
}
