/*
 * File Name:	5491.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.11 18:15
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

int MOD;

inline int add() {return 0;}
template <typename ...T>
inline int add(int arg, T... args)
{
	int res = arg + add(args...);
	if (res >= MOD) res -= MOD;
	return res;
}

inline int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}

inline int mul() {return 1;}
template <typename ...T>
inline int mul(int arg, T... args)
{
	long long res = 1ll * arg * mul(args...);
	if (res >= MOD) res %= MOD;
	return res;
}

int qpow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
int a, II;
struct num
{
	int x, y;
	inline num(int x = 0, int y = 0) : x(x), y(y) {}
	inline num operator * (num B) {return num(add(mul(x, B.x), mul(II, y, B.y)), add(mul(x, B.y), mul(y, B.x)));}
	inline num operator *=(num B) {return *this = *this * B;}
};

num qpow(num base, int b)
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

int main()
{
#ifdef CraZYali
	file("5491");
#endif
	register int T(read<int>());
	while (T--)
	{
		int n = read<int>();
		MOD = read<int>();
		if (!n)
		{
			puts("0");
			continue;
		}
		if (qpow(n, MOD - 1 >> 1) != 1)
		{
			puts("Hola!");
			continue;
		}
		a = MOD - 1;
		while (1)
		{
			II = sub(mul(a, a), n);
			if (a && qpow(II, MOD - 1 >> 1) == MOD - 1) break;
			a = rand() % MOD;
		}
		int ans1 = qpow(num(a, 1), MOD + 1 >> 1).x, ans2 = sub(0, ans1);
		if (ans1 == ans2) printf("%d\n", ans1);
		else printf("%d %d\n", min(ans1, ans2), max(ans1, ans2));
	}
	return 0;
}
