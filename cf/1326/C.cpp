/*
	Problem:	C.cpp
	Time:		2020-03-19 23:35
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
const int maxn = 2e5 + 10, MOD = 998244353, inv2 = MOD + 1 >> 1;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
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

int n, k, p[maxn], pos[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) pos[p[i] = read<int>()] = i;
	int ans = 1;
	int lst = 0, first = 1;
	REP(i, 1, n)
	{
		lst++;
		if (p[i] >= n - k + 1)
		{
			if (first) first = 0;
			else ans = mul(ans, lst);
			lst = 0;
		}
	}
	cout << k * (n + n - k + 1ll) / 2 << ' ' << ans << endl;
	return 0;
}
