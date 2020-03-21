/*
	Problem:	4980.cpp
	Time:		2020-03-21 11:55
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
#define i64 long long
using namespace std;
const int MOD = 1e9 + 7; 

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

int power_pow(int base, int b)
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

const int LIM = 4e5;
int prime[LIM + 5], p_cnt, Phi[LIM + 5];
bool notp[LIM + 5];
struct __init__
{
	__init__()
	{
		Phi[1] = 1;
		REP(i, 2, LIM)
		{
			if (!notp[i]) Phi[prime[++p_cnt] = i] = i - 1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];if (tmp > LIM) break;
				notp[tmp] = 1;
				if (i % prime[j]) Phi[tmp] = Phi[i] * (prime[j] - 1);
				else {Phi[tmp] = Phi[i] * prime[j];break;}
			}
		}
	}
}__INIT__;

int phi(int n)
{
	if (n <= LIM) return Phi[n];
	int N = n, ans = 1;
	REP(i, 1, p_cnt)
	{
		int p = prime[i];
		if (p * p > n) break;
		else if (n % p == 0)
		{
			N /= p;
			ans = mul(ans, p - 1);
			while (n % p == 0) n /= p;
		}
	}
	if (n > 1)
	{
		N /= n;
		ans = mul(ans, n - 1);
	}
	return mul(ans, N);
}

int calc(int n)
{
	long long ans = 0;
	for (int g = 1; g * g <= n; g++) if (n % g == 0)
	{
		ans += mul(power_pow(n, g - 1), phi(n / g));
		if (g * g != n) ans += mul(power_pow(n, n / g - 1), phi(g));
	}
	return ans % MOD;
}

int main()
{
#ifdef CraZYali
	file("4980");
#endif
	register int T = read<int>();
	while (T--) cout << calc(read<int>()) << '\n';
	return 0;
}
