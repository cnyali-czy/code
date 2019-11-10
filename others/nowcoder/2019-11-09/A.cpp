/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.09 18:34
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1e6 + 10, MOD = 1e9 + 7;

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

int n;
int a[maxn], bin[maxn];

long long ans;

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	sort(a + 1, a + 1 + n);
	bin[0] = 1;
	REP(i, 1, n) bin[i] = bin[i-1] * 2 % MOD;
	REP(i, 1, n)
	{
		(ans -= a[i] * (bin[n - i] - 1) % MOD) %= MOD;
		(ans += a[i] * (bin[i - 1] - 1) % MOD) %= MOD;
	}
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
