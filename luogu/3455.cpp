/*
 * File Name:	3455.cpp
 * Author	:	CraZYali
 * Time		:	2019.12.20 15:42
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
const int maxn = 50000 + 10;
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

char mu[maxn];
int prime[maxn], p_cnt, sum[maxn];
bool notp[maxn];

struct __init__
{
	__init__(const int N = 50000)
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
			sum[i] = sum[i-1] + mu[i];
		}
	}
}__INIT__;

int main()
{
#ifdef CraZYali
	file("3455");
#endif
	register int T(read<int>());
	while (T--)
	{
		int n(read<int>()), m(read<int>()), k(read<int>());
		if (n > m) swap(n, m);
		n /= k;m /= k;
		long long ans(0);
		for (int i = 1, j; i <= n; i = j + 1)
		{
			j = min(n / (n / i), m / (m / i));
			ans += 1ll * (sum[j] - sum[i-1]) * (n / i) * (m / i);
		}
		cout << ans;putchar(10);
	}
	return 0;
}
