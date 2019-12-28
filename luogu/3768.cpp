#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
using namespace std;
const int N = 4.7e6;

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
int MOD, inv2, inv3, inv6;

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
	register long long res(1ll * x * y);
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
long long n;

int prime[N + 5], p_cnt, phi[N + 5], sum[N + 5];
bool notp[N + 5];

inline void init()
{
	phi[1] = sum[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) phi[prime[++p_cnt] = i] = i - 1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];
			if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j]) phi[tmp] = phi[i] * (prime[j] - 1);
			else
			{
				phi[tmp] = phi[i] * prime[j];
				break;
			}
		}
		sum[i] = add(sum[i-1], mul(mul(i, i), phi[i]));
	}
}

inline int S1(long long n)
{
	if (n >= MOD) n %= MOD;
	return mul(n, mul(n + 1, inv2));
}
inline int S2(long long n)
{
	if (n >= MOD) n %= MOD;
	return mul(n, mul(n + 1, mul(n + n + 1, inv6)));
}
inline int S2(long long l, long long r)
{
	return sub(S2(r), S2(l-1));
}
unordered_map <long long, int> mem;
int S(long long n)
{
	if (n <= N) return sum[n];
	if (mem[n]) return mem[n];
	int res(mul(S1(n), S1(n)));
	for (long long i = 2, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		res = sub(res, mul(S2(i, j), S(n / i)));
	}
	return mem[n] = res;
}

signed main()
{
#ifdef CraZYali
	file("3768");
#endif
	cin >> MOD >> n;
	inv2 = MOD + 1 >> 1;
	inv3 = inv(3);
	inv6 = mul(inv2, inv3);
	init();
	int ans(0);
	for (long long i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		int tmp = S1(n / i);
		tmp = mul(tmp, tmp);
		ans = add(ans, mul(tmp, sub(S(j), S(i-1))));
	}
	cout << ans << endl;
	return 0;
}
