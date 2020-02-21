/*
	Problem:	B.cpp
	Time:		2020-02-21 10:20
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
#include <unordered_map>
#define int long long
using namespace std;
const int MOD = 998244353, inv2 = MOD + 1 >> 1;

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

unordered_map <int, int> mem;
int solve(int x)
{
	if (x <= 1) return x ? 2 : 0;
	if (mem.count(x)) return mem[x];
	return mem[x] = (solve(x >> 1) + (x + 1 >> 1) + 1ll * inv2 * (solve(x + 1 >> 1) + solve(x - 1 >> 1)) % MOD) % MOD;
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--) {int l(read<int>()), r(read<int>());printf("%d\n", (MOD + solve(r) - solve(l - 1)) % MOD);}
	return 0;
}
