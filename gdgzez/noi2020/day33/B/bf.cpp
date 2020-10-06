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

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e7 + 10;

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

int n, k;

int prime[maxn], p_cnt, to[maxn];
bool notp[maxn];
unsigned mu[maxn];
void init(int N)
{
	mu[1] = 1;to[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) mu[prime[++p_cnt] = i] = -1, to[i] = i;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j]) to[tmp] = to[i] * prime[j], mu[tmp] = -mu[i];
			else {to[tmp] = to[i];break;}
		}
	}
}
unsigned mem[maxn];
unsigned f(int x)
{
	if (x == 1) return k;
	unsigned &res = mem[x];
	if (res) return res;
	int Max = 1, tot = 0;
	REP(i, 1, p_cnt)
	{
		int p = prime[i];
		if (1ll * p * p > x) break;
		int c = 0;
		while (x % p == 0)
		{
			c++;
			x /= p;
		}
		tot += c;
		if (Max < c) Max = c;
		if (Max > k) return res = 0;
	}
	if (x > 1) tot++;
	return res = ((tot & 1) ? -1 : 1) * (k - Max + 1);
}
int main()
{
	freopen("B.in","r",stdin);
	freopen("bf.out","w",stdout);
	cin >> n >> k;
	init(n);
	unsigned ans = 0;
	REP(d, 1, n) if (mu[d])
		REP(g, 1, n / d)
		{
			int T = d * g;
			ans += mu[d] * (n / T) * (n / T) * f(g);
		}
	cout << ans % (1 << 30) << endl;
	return 0;
}
