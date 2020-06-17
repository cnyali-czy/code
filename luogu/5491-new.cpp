/*
	Problem:	5491-new.cpp
	Time:		2020-06-17 15:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;
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

namespace Less
{
	int n, p;
	i64 i2;
	struct num
	{
		int a, b;
		num(int a = 0, int b = 0) : a(a), b(b) {}
		num operator + (num B) {return num((a + B.a) % p, (b + B.b) % p);}
		num operator * (num B)
		{
			int c = B.a, d = B.b;
			return num((1ll * a * c + 1ll * b * d % p * i2) % p, (1ll * a * d + 1ll * b * c) % p);
		}
		num operator *=(num B) {return *this = *this * B;}
	};
	num power_pow(num base, int b)
	{
		num ans(1);
		while (b)
		{
			if (b & 1) ans *= base;
			base *= base;
			b >>= 1;
		}
		return ans;
	}
	i64 power_pow(i64 base, int b)
	{
		i64 ans = 1;
		while (b)
		{
			if (b & 1) (ans *= base) %= p;
			(base *= base) %= p;
			b >>= 1;
		}
		return ans;
	}
	bool judge(int x)
	{
		return power_pow(x, p - 1 >> 1) == 1;
	}
	void solve()
	{
		n = read<int>();
		p = read<int>();
		if (!n) return void(puts("0"));
		if (!judge(n)) return void(puts("Hola!"));
		while (1)
		{
			int a = rand() % p;
			i2 = (1ll * a * a + p - n) % p;
			if (judge(i2)) continue;
			int x = power_pow(num(a, 1), p + 1 >> 1).a;
			int y = p - x;
			if (x > y) swap(x, y);
			printf("%d %d\n", x, y);
			return;
		}
	}
}

int main()
{
#ifdef CraZYali
	file("5491-new");
#endif
	REP(Case, 1, read<int>()) Less :: solve();
	return 0;
}
