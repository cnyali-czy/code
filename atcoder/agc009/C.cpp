/*
	Problem:	2292.cpp
	Time:		2021-05-14 08:53
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
const int maxn = 1e5 + 10, MOD = 1e9 + 7;

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

int n, A, B, a[maxn];
int f[maxn], s[maxn];

signed main()
{
#ifdef CraZYali
	file("2292");
#endif
	n = read<int>();A = read<int>();B = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	if (A < B) swap(A, B);
	
	REP(i, 1, n - 2) if (a[i + 2] - a[i] < B)
	{
		puts("0");
		return 0;
	}
	f[0] = s[0] = 1;
	int p = 0, q = 0;
	REP(i, 1, n)
	{
		while (p < i && a[i] - a[p + 1] >= A) p++;
		if (q <= p) f[i] = (s[p] - (q ? s[q - 1] : 0)) % MOD;
		s[i] = (s[i - 1] + f[i]) % MOD;
		if (i > 1 && a[i] - a[i - 1] < B) q = i - 1;
	}
	int ans = 0;
	DEP(i, n, 0)
	{
		ans += f[i];
		if (i < n && a[i + 1] - a[i] < B) break;
	}
	cout << (ans % MOD + MOD) % MOD << endl;
	
	return 0;
}
