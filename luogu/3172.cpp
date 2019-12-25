/*
 * File Name:	3172.cpp
 * Author	:	CraZYali
 * Time		:	2019.12.20 14:25
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <unordered_map>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 1e9 + 7, N = 1.5e6;

inline int add(int x, int y)
{
	register int res(x + y);
	if (res >= MOD) res -= MOD;
	return res;
}
inline int sub(int x, int y)
{
	register int res(x - y);
	if (res < 0) res += MOD;
	return res;
}
inline int mul(int x, int y)
{
	long long res(1ll * x * y);
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

int prime[N + 5], p_cnt, sum[N + 5], mu[N + 5];
bool notp[N + 5];
struct __init__
{
	__init__()
	{
		mu[1] = sum[1] = 1;
		REP(i, 2, N)
		{
			if (!notp[i]) mu[prime[++p_cnt] = i] = MOD - 1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > N) break;
				notp[tmp] = 1;
				if (i % prime[j]) mu[tmp] = MOD - mu[i];
				else break;
			}
			sum[i] = add(sum[i-1], mu[i]);
		}
	}
}__INIT__;

unordered_map <int, int> mem;
int S(int n)
{
	if (n <= N) return sum[n];
	if (mem.count(n)) return mem[n];
	int res(1);
	for (int i = 2, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		res = sub(res, mul(j - i + 1, S(n / i)));
	}
	return mem[n] = res;
}

int n, k, L, R;

int main()
{
#ifdef CraZYali
	file("3172");
#endif
	cin >> n >> k >> L >> R;
	int RR = R / k, LL = (L - 1) / k, ans(0);
	for (int i = 1, j; i <= RR; i = j + 1)
	{
		if (i <= LL && LL) j = min(LL / (LL / i), RR / (RR / i));
		else j = RR / (RR / i);
		ans = add(ans, mul(sub(S(j), S(i-1)), power_pow(sub(RR / i, LL / i), n)));
	}
	cout << ans << endl;
	return 0;
}
