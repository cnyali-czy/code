/*
	Problem:	6846.cpp
	Time:		2020-10-11 22:23
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
const int maxn = 18, MOD = 998244353, inv2 = MOD + 1 >> 1, maxm = maxn * maxn;

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

int cnt[1 << 9];
struct __init__
{
	__init__()
	{
		REP(i, 1, (1 << 9) - 1) cnt[i] = cnt[i & (i - 1)] + 1;
	}
}__INIT__;
inline int count(int x) {return cnt[x & 511] + cnt[x >> 9];}
inline i64 sgn(int x) {return x & 1 ? MOD - 1 : 1;}

int n, m;
bool G[maxn][maxn];
int f[1 << maxn];
bool ok[1 << maxn];
int x[maxm], y[maxm];

int main()
{
#ifdef CraZYali
	file("6846");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, m) x[i] = read<int>() - 1, y[i] = read<int>() - 1;
	f[0] = 1;
	ok[0] = 1;
	REP(S, 1, (1 << n) - 1)
	{
		ok[S] = 1;
		REP(i, 1, m) if ((S >> x[i] & 1) && (S >> y[i] & 1))
		{
			ok[S] = 0;
			break;
		}
		for (int x = S; x; x = (x - 1) & S)
			if (ok[x])
				f[S] = (f[S] + 1ll * f[x ^ S] * sgn(1 + count(x))) % MOD;
	}
	cout << 1ll * f[(1 << n) - 1] * inv2 % MOD * m % MOD << endl;
	return 0;
}
