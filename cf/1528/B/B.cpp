/*
	Problem:	B.cpp
	Time:		2021-06-24 14:48
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
const int maxn = 1e6 + 10, MOD = 998244353;

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

int n, f[maxn], c[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) REP(j, 1, n / i) f[i * j]++;
	i64 sum = 0;
	REP(i, 1, n)
	{
		f[i] = (f[i] + sum) % MOD;
		sum += f[i];
	}
	cout << f[n] << endl;
	return 0;
}
