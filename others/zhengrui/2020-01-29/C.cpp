/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.29 09:18
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 30000 + 10, maxm = 30000 + 10, MOD = 998244353;

int add() {return 0;}
template <typename ...T>
int add(int x, T... y)
{
	int res = x + add(y...);
	if (res >= MOD) res -= MOD;
	return res;
}

int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}

int mul() {return 1;}
template <typename ...T>
int mul(int x, T... y)
{
	long long res = (long long)x * mul(y...);
	if (res >= MOD) res %= MOD;
	return res;
}

int power_pow(int base, int b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, m, a[maxn];
int dp[maxn], s[maxn], lst[10];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		const int k = read<int>();
		m = read<int>();
		REP(i, 1, n) a[i] = read<int>() % k;
		while (m--)
		{
			int o(read<int>()), l(read<int>()), r(read<int>());
			if (o == 1)
			{
				int x = read<int>() % k;
				REP(i, l, r)
				{
					a[i] += x;
					if (a[i] >= k) a[i] -= k;
				}
			}
			else if (o == 2)
			{
				int x = read<int>() % k;
				REP(i, l, r)
				{
					a[i] *= x;
					if (a[i] >= k) a[i] %= k;
				}
			}
			else
			{
				REP(i, 0, k - 1) lst[i] = 0;
				dp[l] = 1;
				lst[a[l]] = l;
				s[l] = 1;s[l-1] = 0;
				REP(i, l + 1, r)
				{
					dp[i] = sub(s[i - 1], (lst[a[i]] ? s[lst[a[i]] - 1] : MOD - 1));
					lst[a[i]] = i;
					s[i] = add(s[i-1], dp[i]);
				}
				int ans = 0;
				REP(i, l, r) ans = add(ans, dp[i]);
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
