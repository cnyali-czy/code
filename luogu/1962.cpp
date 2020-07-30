/*
	Problem:	1962.cpp
	Time:		2020-07-30 23:17
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

using namespace std;
const int MOD = 1e9 + 7, inv2 = MOD + 1 >> 1;
#define i64 long long
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

struct num
{
	int a, b;//a + b * sqrt(5)
	inline num(int a = 0, int b = 0) : a(a), b(b) {}
	inline num operator - (num B) {return num((a - B.a) % MOD, (b - B.b) % MOD);}
	inline num operator * (num B) {return num((1ll * a * B.a + 5ll * b * B.b) % MOD, (1ll * a * B.b + 1ll * b * B.a) % MOD);}
	inline num operator *=(num B) {return *this = *this * B;}
};
num power_pow(num base, i64 b)
{
	num ans = 1;
	while (b)
	{
		if (b & 1) ans *= base;
		base *= base;
		b >>= 1;
	}
	return ans;
}
int fib(i64 n)
{
	num base1(inv2,	 inv2);
	num base2(inv2,	-inv2);
	return (MOD + (power_pow(base1, n) - power_pow(base2, n)).b) % MOD;
}

int main()
{
#ifdef CraZYali
	file("1962");
#endif
	i64 n;
	cin >> n;
	cout << fib(n) << endl;
	return 0;
}
