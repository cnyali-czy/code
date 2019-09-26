#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

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

namespace polynomial
{
	const int MOD = 998244353;
	int power_pow(long long base, int b)
	{
		long long ans(1);
		while (b)
		{
			if (b & 1) (ans *= base) %= MOD;
			(base *= base) %= MOD;
			b >>= 1;
		}
		return ans;
	}
#define inv(x) power_pow(x, MOD - 2)
	const int L = 18, len = 1 << L, invN = inv(len);
	int R[len];bool prepared(0);
	inline void NTT(int a[], int flag)
	{
		if (!prepared)
		{
			prepared = 1;
			REP(i, 0, len - 1) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
		}
		REP(i, 1, len - 1)
			if (i < R[i]) swap(a[i], a[R[i]]);
		for (int i(1); i < len; i <<= 1)
		{
			int wn = power_pow(3, (MOD - 1) / (i << 1));
			if (flag < 0) wn = inv(wn);
			for (int k(0); k < len; k += i << 1)
			{
				long long w(1);
				for (int l(0); l < i; l++, (w *= wn) %= MOD)
				{
					int x(a[k + l]), y(w * a[k + l + i] % MOD);
					a[k + l] = (x + y) % MOD;
					a[k + l + i] = (x - y) % MOD;
				}
			}
		}
		if (flag < 0)
			REP(i, 0, len - 1) a[i] = 1ll * a[i] * invN % MOD;
	}
#undef inv(x)
	inline void mul(int res[], int a[], int b[])
	{
		NTT(a, 1);NTT(b, 1);
		REP(i, 0, len - 1) res[i] = 1ll * a[i] * b[i] % MOD;
		NTT(a, -1);NTT(b, -1);
		NTT(res, -1);
	}
	inline void add(int res[], int a[], int b[])
	{
		NTT(a, 1);NTT(b, 1);
		REP(i, 0, len - 1) res[i] = (a[i] + b[i]) % MOD;
		NTT(a, -1);NTT(b, -1);
		NTT(res, -1);
	}
}

int m, n, k;
int a[1<<18], b[1<<18], c[1<<18];

int main()
{
#ifdef CraZYali
	file("34");
#endif
	cin >> n >> m;
	REP(i, 0, n) a[i] = read<int>();
	REP(i, 0, m) b[i] = read<int>();
	polynomial::mul(c, a, b);
	REP(i, 0, n + m) printf("%d%c", (polynomial::MOD+c[i])%polynomial::MOD, i == n + m ? '\n' : ' ');
	return 0;
}
