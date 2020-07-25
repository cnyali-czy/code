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

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e7 + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

long long n, k;

int prime[maxn], p_cnt, phi[maxn], N, Min[maxn];
bool notp[maxn];
unsigned sphi[maxn];
void init(int qaq)
{
	N = qaq;
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
		for (unsigned i = 2, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res -= s(n / i) * (j - i + 1);
		}
		return res;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> k;
	init(n);
	unsigned ans = 0;
	REP(g, 1, n) ans += f(g) * (2 * SPHI :: s(n / g) - 1);
	cout << ans % (1 << 30) << endl;
	return 0;
}
