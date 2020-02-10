/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.07 12:06
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
int MOD = 998244353;
const int Inv2 = MOD + 1 >> 1;
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

int add(int x, int y)
{
	int res = x + y;
	if (res >= MOD) return res - MOD;
	return res;
}
inline void inc(int &x, int y)
{
	x += y;
	if (x >= MOD) x -= MOD;
}
int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) return res + MOD;
	return res;
}
int mul(int x, int y)
{
	long long res = (long long)x * y;
	if (res >= MOD) return res % MOD;
	return res;
}

struct Num // a + b Sqrt 5
{
	int a, b;
	Num(int a = 0, int b = 0) : a(a), b(b) {}
	inline Num operator + (const Num &B) {return Num(add(a, B.a), add(b, B.b));}
	inline Num operator - (const Num &B) {return Num(sub(a, B.a), sub(b, B.b));}
	inline Num operator * (const Num &B) {return Num(add(mul(a, B.a), mul(mul(5, b), B.b)), add(mul(a, B.b), mul(b, B.a)));}
	inline Num operator *=(const Num &B) {return *this = *this * B;}
}x1 = Num(Inv2, Inv2), x2 = Num(Inv2, MOD - Inv2);

Num power_pow(Num base, long long b)
{
	Num ans(1);
	while (b)
	{
		if (b & 1) ans *= base;
		base *= base;
		b >>= 1;
	}
	return ans;
}

inline int Fib_MOD(long long n)
{
	Num x1n = power_pow(x1, n), x2n = power_pow(x2, n), up = x1n - x2n;
	return up.b;
}
int fib[15];
#define i64 long long
namespace run
{
	int p;
	struct Mat
	{
		int a[2][2];
		Mat() {memset(a, 0, sizeof a);}
		inline int* operator [] (int x) {return a[x];}
		inline Mat operator * (Mat b)
		{
			Mat res;
			REP(i, 0, 1)
				REP(k, 0, 1) if (a[i][k])
				REP(j, 0, 1) inc(res[i][j], mul(a[i][k], b[k][j]));
			return res;
		}
		inline Mat operator *=(Mat b) {return *this = *this * b;}
	}f, g;
	inline int solve(i64 n, int p)
	{
		MOD = p;
		f = g = Mat();
		f[0][0] = g[0][0] = g[0][1] = g[1][0] = 1;
		n--;
		while (n)
		{
			if (n & 1) f *= g;
			g *= g;
			n >>= 1;
		}
		MOD = 998244353;
		return f[0][0];
	}
	i64 n;
	int T, a, b, c, d, ans;
	int main()
	{
		register int T = read<int>();
		while (T--)
		{
			n = read<long long>();
			a = read<int>(), b = read<int>(), c = read<int>(), d = read<int>();
			while (c)
			{
				int x = c, y = a / c;
				c = a - y * c;
				a = x;
				b -= y * d;
				swap(b, d);
			}
			if (d < 0) d *= -1;
			if (b < 0) b += (-b + d - 1) / d * d;
			if (!d)
			{
				solve(n+1, MOD);
				ans = (1ll * a * f[0][1] + 1ll * b * f[0][0]) % MOD;
			}
			else if (!a) ans = 1ll * __gcd(b, d) * solve(n + 1, MOD) % MOD;
			else
			{
				int x = __gcd(a, solve(n+1, a * d));
				ans = 1ll * x * __gcd(((1ll * a * f[0][1] + 1ll * b * f[0][0]) % (x * d) / x), d) % MOD;
			}
			ans = (ans + MOD) % MOD;
			printf("%lld\n", ans);
		}
		return 0;
	}
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
	register int T = read<int>();
	fib[1] = 1;
	REP(i, 2, 11) fib[i] = fib[i-1] + fib[i-2];
	while (T--)
	{
		long long n = read<long long>();
		int a = read<int>(), b = read<int>(), c = read<int>(), d = read<int>();
		if (n <= 10 || 1) printf("%lld\n", __gcd((1ll * a * Fib_MOD(n) + 1ll * b * Fib_MOD(n+1)) % MOD, (1ll * c * Fib_MOD(n) + 1ll * d * Fib_MOD(n + 1)) % MOD));
		else if (!b && !d) printf("%d\n", mul(Fib_MOD(n), __gcd(a, c)));
	}
	return 0;
}

