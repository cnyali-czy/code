#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10, MOD = 1e9 + 7;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, m, k;

int str[5][4], fac[10];
int bin[maxn], u[maxn], v[maxn];

//sum cur * 2 ^ (n - w) * str(k, m) * m!

namespace two
{
	int G[maxn];
	int work()
	{
		i64 ans = 0;
		
		//m = 1, w = 2
		ans = 1ll * m * bin[n - 2] % MOD * str[2][1] % MOD;
		//m = 2, w = 3
		REP(i, 1, m) G[u[i]]++, G[v[i]]++;
		int qaq = 0;
		REP(i, 1, n)
		{
			int cur = 1ll * G[i] * (G[i] - 1) / 2 % MOD;
			qaq = (qaq + cur) % MOD;
			ans = (ans + 1ll * cur * bin[n - 3] * str[k][2] * fac[2]) % MOD;
		}
		//m = 2, w = 4
		int cur = (1ll * m * (m - 1) / 2 + MOD - qaq) % MOD;
		ans = (ans + 1ll * cur * bin[n - 4] * str[k][2] * fac[2]) % MOD;
		return ans % MOD;
	}
}

namespace three
{
	void work()
	{
		i64 ans = two :: work();
		//m = 3, w = 3
		//m = 3, w = 4
		//m = 3, w = 5
		//m = 3, w = 6

		cout << ans % MOD << endl;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, m) u[i] = read<int>(), v[i] = read<int>();
	bin[0] = 1;
	REP(i, 1, n) bin[i] = 2 * bin[i - 1] % MOD;
	str[0][0] = 1;
	str[1][1] = 1;
	str[2][1] = str[2][2] = 1;
	str[3][1] = 1;str[3][2] = 3;str[3][3] = 1;
	fac[0] = 1;fac[1] = 1;fac[2] = 2;fac[3] = 6;fac[4] = 24;fac[5] = 120;
	if (k == 1) printf("%lld\n", 1ll * m * bin[n - 2] % MOD);
	else if (k == 2) printf("%d\n", two :: work());
	else three :: work();
	return 0;
}
