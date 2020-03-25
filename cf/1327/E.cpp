/*
	Problem:	E.cpp
	Time:		2020-03-24 00:11
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
const int maxn = 2e5 + 10, MOD = 998244353;

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

int bin[maxn], n, f[maxn];

int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();
	bin[0] = 1;
	REP(i, 1, n) bin[i] = mul(bin[i - 1], 10);
	int ss = 0, s = 0;
	DEP(i, n, 1)
	{
		inc(f[i], sub(mul(n - i + 1, bin[n - i + 1]), ss));
		inc(s, f[i]);
		inc(ss, add(s, f[i]));
	}
	REP(i, 1, n) cout << f[i] << ' ';
	return 0;
}
