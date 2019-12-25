/*
 * File Name:	576.cpp
 * Author	:	CraZYali
 * Time		:	2019.12.20 18:55
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 10, MOD = 998244353;

inline int add(int x, int y)
{
	int res(x + y);
	if (res >= MOD) res -= MOD;
	return res;
}
inline int sub(int x, int y)
{
	int res(x - y);
	if (res < 0) res += MOD;
	return res;
}
inline int mul(int x, int y)
{
	long long res(1ll * x * y);
	if (res >= MOD) res %= MOD;
	return res;
}

int power_pow(int base, int b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, m, a[maxn], c[maxn], ans(1);

int tmp[maxn];

int main()
{
#ifdef CraZYali
	file("576");
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, n) ans = mul(ans, a[i] = read<int>());
	c[0] = 1;
	REP(i, 1, n)
	{
		REP(j, 0, i - 1) tmp[j] = mul(a[i], c[j]);
		REP(j, 1, i) tmp[j] = sub(tmp[j], c[j-1]);
		copy(tmp, tmp + i + 1, c);
	}
	int tmp(1), invn(inv(n));
	REP(i, 0, min(n, m))
	{
		ans = sub(ans, mul(c[i], tmp));
		tmp = mul(tmp, mul(sub(m, i), invn));
	}
	cout << ans << endl;
	return 0;
}
