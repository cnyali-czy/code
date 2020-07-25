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

#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e7 + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

long long n, k;

int prime[maxn], p_cnt, phi[maxn], N, Min[maxn];
bool notp[maxn];
unsigned mu[maxn], sphi[maxn];
void init(int qaq)
{
	N = qaq;
	mu[1] = phi[1] = sphi[1] = 1;
	Min[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) mu[prime[++p_cnt] = i] = -1, phi[i] = i - 1, Min[i] = i;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j]) mu[tmp] = -mu[i], phi[tmp] = phi[i] * (prime[j] - 1), Min[tmp] = prime[j];
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
		res = (unsigned)n * (n + 1) / 2;
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
	freopen("B.in", "r", stdin);
	freopen("bbf.out", "w", stdout);
	cin >> n >> k;
	init(n);
	unsigned ans = 0;
	/*
	REP(d, 1, n) if (mu[d])
		REP(g, 1, n / d)
		{
			int T = d * g;
			ans += mu[d] * (n / T) * (n / T) * f(g);
		}
	*/

	for (i64 i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		i64 N = i;
		unsigned int ccc = 0;
		REP(g, 1, N) ccc += f(g);
		cout << N << ' ' << ccc << endl;
	}
	unsigned ccc=0;
	REP(g, 1, n) ccc+=f(g);
	REP(i,1,n)REP(j,1,n/i)
	{
		if(__gcd(i,j)==1)cerr<<f(i)*f(j)<<' '<<f(i*j)<<endl;
	}
	return 0;
}
