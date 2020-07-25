/*
	Problem:	B.cpp
	Time:		2020-07-24 08:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int MOD = 1 << 30, N = 1e6, maxn = N + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

long long n, k;

int prime[maxn], p_cnt, phi[maxn], Min[maxn];
bool notp[maxn];
unsigned sphi[maxn];
void init()
{
	phi[1] = sphi[1] = 1;
	Min[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) phi[prime[++p_cnt] = i] = i - 1, Min[i] = i;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j]) phi[tmp] = phi[i] * (prime[j] - 1), Min[tmp] = prime[j];
			else {phi[tmp] = phi[i] * prime[j];Min[tmp] = Min[i];break;}
		}
		sphi[i] = sphi[i - 1] + phi[i];
	}
}
unsigned mem[maxn];
unsigned f(int x)
{
	if (x == 1) return k;
	unsigned &res = mem[x];
	if (res) return res;
	int Max = 1, tot = 0;
	while (x > 1)
	{
		int c = 0, t = Min[x];
		while (x % t == 0)
		{
			c++;
			x /= t;
		}
		if (Max < c) Max = c;
		if (Max > k) return res = 0;
		tot += c;
	}
	return res = ((tot & 1) ? -1 : 1) * (k - Max + 1);
}

namespace SPHI
{
	unsigned mem[maxn];
	unsigned s(unsigned n)
	{
		if (n <= N) return sphi[n];
		unsigned &res = mem[::n / n];
		if (res) return res;
		res = n * (n + 1) / 2;
		int div = sqrt(n);
		REP(i, 2, div) res -= s(n / i);
		for (unsigned i = div + 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res -= s(n / i) * (j - i + 1);
		}
		return res;
	}
}

unsigned sf[maxn];

namespace Min25
{
	const int N = 1e6, maxn = N + 10;
	int lim;
	i64 n, Sqr, tot, w[maxn];
	unsigned g0[maxn];
	i64 mem1[maxn], mem2[maxn];

	unsigned g(i64 x, int y)
	{
		if (prime[y] >= x) return 0;
		i64 k = x <= Sqr ? mem1[x] : mem2[n / x];
		unsigned ans = -(g0[k] - y);
		REP(i, y + 1, p_cnt)
		{
			i64 pe = prime[i]; if (pe * pe > x) break;
			for (int e = 1; pe <= x && e <= lim; e++, pe *= prime[i])
				ans += ((e & 1) ? -1 : 1) * ((e > 1) + g(x / pe, i));
		}
		return ans;
	}

	unordered_map <i64, unsigned> shit;
	unsigned calc(i64 qaq)
	{
		if (qaq <= N) return sf[qaq];
		if (shit[qaq]) return shit[qaq];
		n = qaq;
		Sqr = sqrt(n);
		tot = 0;
		for (i64 i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			w[++tot] = n / i;
			unsigned x = w[tot] % MOD;
			g0[tot] = x - 1;
			if (n / i <= Sqr) mem1[n / i] = tot;
			else mem2[n / (n / i)] = tot;
		}
		REP(i, 1, p_cnt)
		{
			const i64 p = prime[i];
			REP(j, 1, tot)
			{
				if (p * p > w[j]) break;
				i64 fff = w[j] / p;
				i64 k = fff <= Sqr ? mem1[fff] : mem2[n / fff];
				g0[j] -= g0[k] - (i - 1);
			}
		}
		unsigned res = 0;
		for (lim = 1; lim <= k; lim++) res += g(n, 0) + 1;
		return shit[qaq] = res;
	}
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> k;
	init();
	REP(i, 1, N) sf[i] = sf[i - 1] + f(i);
	int div = sqrt(n);
	unsigned ans = 0;
	REP(i, 1, div) ans += f(i) * (2 * SPHI :: s(n / i) - 1);
	for (i64 i = div + 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		ans += (Min25 :: calc(j) - Min25 :: calc(i - 1)) * (2 * SPHI :: s(n / i) - 1);
	}
	/*
	int times = 20;
	while (times--)
	{
		int nn = 1ll * rand() * rand() % n + 1;
		unsigned check = 0, res = Min25 :: calc(nn);
		REP(i, 1, nn) check += f(i);
		
		printf("%d : %u = %u\n",nn, check,res);
		assert(check == res);
	}
*/
//	REP(g, 1, n) ans += f(g) * (2 * SPHI :: s(n / g) - 1);
	cout << ans % MOD << endl;
	return 0;
}
