/*
	Problem:	4378.cpp
	Time:		2020-11-23 21:55
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
#define int long long

using namespace std;
const int maxn = 10000 + 10;

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

int prime[maxn], notp[maxn], p_cnt;
struct __init__
{
	__init__(const int n = 10000)
	{
		REP(i, 2, n)
		{
			if (!notp[i]) prime[++p_cnt] = i;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > n) break;
				notp[tmp] = 1;
				if (i % prime[j] == 0) break;
			}
		}
	}
}__INIT__;
int n;
int a[maxn], b[maxn], ans[maxn][maxn];
int lcm(int x, int y) {if (!x || !y) return x | y;return x / __gcd(x, y) * y;}
int A(int x, int y)
{
	return x < 0 || x >= n || y < 0 || y >= n ? 0 : ans[x][y];}
signed main()
{
#ifdef CraZYali
	file("4378");
#endif
	n = read<int>();
	if (n == 2)
	{
		puts("4 7");
		puts("23 10");
		return 0;
	}
	int m = 0;
	REP(i, 0, n - 1 + n - 1) a[i] = prime[++m];
	REP(i, 0, n - 1 + n - 1) b[i] = prime[++m];
	REP(i, 0, n - 1) REP(j, 0, n - 1) if (!(i + j & 1))
		ans[i][j] = prime[i + j + 2 >> 1] * prime[n + (i - j >> 1) + (n + 1 >> 1)];
	REP(i, 0, n - 1) REP(j, 0, n - 1) if (!ans[i][j])
		ans[i][j] = 1 + lcm(lcm(A(i, j - 1), A(i, j + 1)), lcm(A(i - 1, j), A(i + 1, j)));
	REP(i, 0, n - 1) REP(j, 0, n - 1) printf("%lld%c", ans[i][j], j == end_j ? '\n' : ' ' );
	return 0;
}
