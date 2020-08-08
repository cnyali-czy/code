/*
	Problem:	C.cpp
	Time:		2020-08-08 19:39
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
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cstdio>
using namespace std;
#define i64 long long
const int maxn = 2e5 + 10;

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

inline int randint(int l, int r) {return rand() % (r - l + 1) + l;}
int n, p;
i64 k, x[maxn], y[maxn];

int power_pow(int base, int b, const int MOD = p)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, p - 2)

inline i64 mul(int i, int j) {return x[i] * x[j] + y[i] * y[j];}
namespace bf
{
	int main()
	{
		REP(i, 1, n) REP(j, i, n) if (mul(i, j) == k) {printf("%lld %lld\n", i, j);return 0;}
		return 0;
	}
}

bool isprime(int x)
{
	if (x <= 2) return x == 2;
	for (int i = 2; i * i <= x; i++) if (x % i == 0) return 0;
	return 1;
}
const int N = 540;
int f[N][N][N];

vector <int> v[N][N];

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();k = read<i64>();
	REP(i, 1, n) x[i] = read<int>(), y[i] = read<int>();
	if (n <= 5000) return bf :: main();
	const double sqr = sqrt(n), alpha = .2;
	while (!isprime(p)) p = randint((1 - alpha) * sqr, (1 + alpha) * sqr);
	int kk = k % p;
	cerr << p << endl;
	REP(x1, 0, p - 1) REP(y1, 0, p - 1)
	{
		const int Inv = inv(y1);
		REP(x2, 1, p - 1)
			f[x1][y1][x2] = (kk + p - 1ll * x1 * x2 % p) * Inv % p;
	}
	REP(i, 1, n)  v[x[i] % p][y[i] % p].emplace_back(i);
	REP(i, 1, n)
	{
		int x1 = x[i] % p, y1 = y[i] % p;
		REP(x2, 0, p - 1)
			for (auto j : v[x2][f[x1][y1][x2]])
			{
				if (mul(i, j) == k)
				{
					printf("%lld %lld\n", i, j);
					return 0;
				}
			}
	}
	return 0;
}
