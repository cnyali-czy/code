/*
	Problem:	6229.cpp
	Time:		2020-06-14 21:22
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 1e9 + 7, maxn = 1e6 + 10, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1, inv4 = 1ll * inv2 * inv2 % MOD;
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

inline i64 S(i64 n)
{
	if (n >= MOD) n %= MOD;
	return n * n % MOD * ((1 + 2 * n + n * n) % MOD) % MOD * inv4 % MOD;
}
inline i64 S2(i64 n)
{
	if (n >= MOD) n %= MOD;
	return n * (n + 1) / 2 % MOD * (n + n + 1) % MOD * inv3 % MOD;
}
inline i64 S2(i64 l, i64 r) {return S2(r) - S2(l - 1);}
int prime[maxn], mu[maxn], p_cnt, N;
bool notp[maxn];
i64 ssr[maxn];
void init()
{
	mu[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) mu[prime[++p_cnt] = i] = -1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j]) mu[tmp] = -mu[i];
			else break;
		}
	}
	REP(i, 1, N) if (mu[i])
	{
		int tmp = 1ll * mu[i] * i * i % MOD;
		for (int j = i; j <= N; j += i) ssr[j] += tmp;
	}
	REP(i, 1, N) (ssr[i] += ssr[i - 1]) %= MOD;
}
int n;
i64 ans;

namespace SF
{
	int mem[maxn];
	i64 S(const i64 N)
	{
		if (N <= ::N) return ssr[N];
		int &res = mem[n / N];
		if (res) return res;
		i64 tmp = -N;
		for (i64 i = 2, j; i <= N; i = j + 1)
		{
			j = N / (N / i);
			tmp += S2(i, j) * S(N / i) % MOD;
		}
		res = MOD - tmp % MOD;if (res < 0) res += MOD;
		return res;
	}
	i64 S(i64 l, i64 r) {return S(r) - S(l - 1);}
}

int main()
{
#ifdef CraZYali
	file("6229");
#endif
	n = read<int>();
	N = pow(n, 2. / 3);
	init();
	for (i64 i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		ans += S(n / i) * SF :: S(i, j) % MOD;
	}
	ans = (ans + n) % MOD * inv2 % MOD;
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
