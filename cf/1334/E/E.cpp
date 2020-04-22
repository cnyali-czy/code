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
#include <unordered_map>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

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

int m, n, k;
const int MOD = 998244353;

const int N = 4e6;
int fac[N + 5], Inv[N + 5];
int power_pow(long long base, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
struct __init__
{
	__init__()
	{
		fac[0] = 1;
		REP(i, 1, N) fac[i] = 1ll * fac[i-1] * i % MOD;
		Inv[N] = inv(fac[N]);
		DEP(i, N - 1, 0) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
	}
}__INIT__;

const int maxn = 1e5 + 10;
int stack[maxn], top, c[maxn], lim;
int calc()
{
	int n = 0;
	REP(i, 1, lim) if (c[i] > 0) n += c[i];
	long long ans = fac[n];
	REP(i, 1, lim) if (c[i] > 0) 
		(ans *= Inv[c[i]]) %= MOD;
	n = 0;
	REP(i, 1, lim) if (c[i] < 0) n -= c[i];
	(ans *= fac[n]) %= MOD;
	REP(i, 1, lim) if (c[i] < 0)
		(ans *= Inv[-c[i]]) %= MOD;
	return ans;
}
int main()
{
#ifdef CraZYali
	file("E");
#endif
	srand(time(0));
	long long D;
	cin >> D;
	vector <long long> qaq;
	for (long long i = 2; i * i <= D; i++) if (D % i == 0)
	{
		qaq.emplace_back(i);
		while (D % i == 0) D /= i;
	}
	if (D > 1) qaq.emplace_back(D);
	lim = qaq.size();
	int q;
	cin >> q;
	while (q--)
	{
		long long x(read<long long>()), y(read<long long>());
		while (x > 1)
		{
			int cur = 0;
			for (auto d : qaq)
			{
				cur++;
				if (x % d == 0) stack[++top] = cur;
				while (x % d == 0)
				{
					c[cur]++;
					x /= d;
				}
				if (x == 1) break;
			}
		}
		while (y > 1)
		{
			int cur = 0;
			for (auto d : qaq)
			{
				cur++;
				if (y % d == 0) stack[++top] = cur;
				while (y % d == 0)
				{
					c[cur]--;
					y /= d;
				}
				if (y == 1) break;
			}
		}
		cout << calc() << '\n';
		REP(i, 1, top) c[stack[i]] = 0;
		top = 0;
	}
	return 0;
}
