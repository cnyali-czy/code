#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e7 + 10, MOD = 20101009, inv2 = (MOD + 1) / 2, inv4 = 1ll * inv2 * inv2 % MOD;

int prime[maxn], p_cnt;
bool notp[maxn];
char mu[maxn];
int sum[maxn];

struct __init__
{
	__init__(const int N = 1e7)
	{
		sum[1] = mu[1] = 1;
		REP(i, 2, N)
		{
			if (!notp[i]) mu[prime[++p_cnt] = i] = -1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > N) break;
				notp[tmp] = 1;
				if (i % prime[j]) mu[tmp] = -mu[i];
				else break;
			}
			sum[i] = (sum[i-1] + 1ll * mu[i] * i * i % MOD) % MOD;
		}
	}
}__INIT__;

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m;

inline int g(int n, int m) {return (1ll * n * (n + 1) % MOD * m % MOD * (m + 1) % MOD * inv4 % MOD) % MOD;}
inline int s(int n, int m)
{
	int res(0);
	for (int i = 1, j; i <= n; i = j + 1)
	{
		j = min(n / (n / i), m / (m / i));
		(res += 1ll * (sum[j] - sum[i-1]) * g(n / i, m / i) % MOD) %= MOD;
	}
	return res;
}
inline int calc(int n, int m)
{
	int res(0);
	for (int i = 1, j; i <= n; i = j + 1)
	{
		j = min(n / (n / i), m / (m / i));
		(res += 1ll * (i + j) * (j - i + 1) % MOD * inv2 % MOD * s(n / i, m / i) % MOD) %= MOD;
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("1829");
#endif
	cin >> n >> m;
	if (n > m) swap(n, m);
	cout << (MOD + calc(n, m)) % MOD << endl;
	return 0;
}
