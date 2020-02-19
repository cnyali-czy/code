/*
	Problem:	B.cpp
	Time:		2020-02-19 20:14
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
#define int long long
using namespace std;
const int MOD = 998244353;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;
int stack[114], top;

inline int phi(int x)
{
	if (x <= 2) return 1;
	int n = x;
	int res = 0;
	top = 0;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0)
		{
			stack[++top] = i;
			while (x % i == 0) x /= i;
		}
	if (x > 1) stack[++top] = x;
	REP(S, 0, (1 << top) - 1)
	{
		int cur = 1, flag = (__builtin_popcount(S) & 1 ? -1 : 1);
		REP(i, 1, top) if (S & (1 << i - 1)) cur *= stack[i];
		res += flag * (n / cur);
	}
	return res % MOD;
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m;
	cout << n % MOD * (m % MOD) % MOD * phi(n) % MOD * phi(m) % MOD << endl;
	return 0;
}
