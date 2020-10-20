/*
	Problem:	B.cpp
	Time:		2020-10-16 16:51
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
const int L = 60;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, p, l[10], r[10];

int C[20][20];

int lucas(int n, int m)
{
	if (n < p && m < p) return C[n][m];
	return C[n % p][m % p] * lucas(n / p, m / p) % p;
}
int calc(int k)
{
	int res = 0;
	REP(i, k, m)
		res += lucas(m, i) * lucas(n + i - k - 1, n - 1);
	return res % p;
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m >> p;
	C[0][0] = 1;
	REP(i, 1, 15)
		REP(j, 0, i) C[i][j] = (C[i - 1][j] + (j ? C[i - 1][j - 1] : 0)) % p;
	REP(i, 1, n) cin >> l[i] >> r[i];
	int ans = 0;
	REP(S, 0, (1 << n) - 1)
	{
		int k = 0, sgn = 1;
		REP(i, 1, n)
			if (S >> (i - 1) & 1) k += l[i];
			else k += r[i] + 1, sgn = -sgn;
		ans += sgn * calc(k);
	}
	cout << (ans % p + p) % p;
	return 0;
}
