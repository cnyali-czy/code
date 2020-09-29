/*
	Problem:	554.cpp
	Time:		2020-09-29 20:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

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
const int MOD = 1e8 + 7;
#define i64 long long
int fac[MOD], Inv[MOD];
i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
struct __init__
{
	__init__()
	{
		fac[0] = 1;
		REP(i, 1, MOD - 1) fac[i] = 1ll * i * fac[i - 1] % MOD;
		Inv[MOD - 1] = inv(fac[MOD - 1]);
		DEP(i, MOD - 2, 0) Inv[i] = 1ll * Inv[i + 1] * (i + 1)%MOD;
	}
}__INIT__;

struct num
{
	vector <int> v;
	num()
	{
		v.resize(1);
	}
	num(int x)
	{
		v = vector<int>(1, x % MOD);
	}
	void clearall()
	{
		while (v.size() > 1 && !v.back()) v.pop_back();
	}
	num operator += (num B)
	{
		if (v.size() < B.v.size()) v.resize(B.v.size());
		v.resize(v.size() + 1);
		REP(i, 0, B.v.size() - 1) v[i] += B.v[i];
		REP(i, 0, v.size() - 1)
		{
			if (v[i] >= MOD)
			{
				v[i + 1] += v[i] / MOD;
				v[i] %= MOD;
			}
		}
		clearall();
		return *this;
	}
	num operator + (num B)
	{
		num tmp = *this;
		tmp += B;
		return tmp;
	}
};
inline int lucas(num A, num B)
{
	if (!B.v.size()) return 1;
	assert(A.v.size());
	i64 res = C(A.v[0], B.v[0]);
	if (B.v.size())
	{
		A.v.erase(A.v.begin());
		B.v.erase(B.v.begin());
		(res *= lucas(A, B)) %= MOD;
	}
	return res;
}
const int maxn = 100;
num fib[maxn];
int f[maxn];
int main()
{
#ifdef CraZYali
	file("554");
#endif
	int n = read<int>();
	fib[1] = 1;fib[2] = 1;
	f[1] = 1;f[2] = 1;
	REP(i, 3, n)
	{
		fib[i] = fib[i-1] + fib[i-2];
		f[i] = (f[i-1] + f[i-2]) % MOD;
	}
	i64 ans = 0;
	REP(i, 2, n)
		ans += 8ll * lucas(fib[i] + fib[i], fib[i]) - 3ll * f[i] * f[i] % MOD - 2 * f[i] - 7;
	cout << (ans % MOD + MOD) % MOD << endl;
	return 0;
}
