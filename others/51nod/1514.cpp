#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 998244353, maxlen = 1 << 18, maxn = 1e5 + 10;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int power_pow(int base, int b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) ans = 1ll * ans * base % MOD;
		base = 1ll * base * base % MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
int R[maxlen];

void NTT(int a[], int len, int flag)
{
	REP(i, 1, len - 1) if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		int wn = power_pow(3, (MOD - 1) / (i * 2));
		if (flag < 0) wn = inv(wn);
		for (int k = 0; k < len; k += i << 1)
		{
			int t = 1;
			for (int l = 0; l < i; l++, t = 1ll * t * wn % MOD)
			{
				int x(a[k + l]), y(1ll * t * a[k + l + i] % MOD);
				a[k + l] = (x + y) % MOD;
				a[k + l + i] = (x - y) % MOD;
			}
		}
	}
	if (flag < 0)
	{
		int invN = inv(len);
		REP(i, 0, len - 1) a[i] = 1ll * a[i] * invN % MOD;
	}
}

int fac[maxlen], ans[maxlen], temp[maxlen];

void calc_inv(int lim, int a[], int b[])
{
	if (!lim) return b[0] = inv(a[0]), void();
	calc_inv(lim >> 1, a, b);
	int len = lim + lim;
	REP(i, 0, len - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? lim : 0);
	copy(a, a + lim, temp);
	NTT(temp, len, 1);
	NTT(b, len, 1);
	REP(i, 0, len - 1) b[i] = b[i] * (2ll - 1ll * temp[i] * b[i] % MOD + MOD) % MOD;
	NTT(b, len, -1);
	REP(i, lim, len - 1) b[i] = 0;
	REP(i, 0, len - 1) temp[i] = 0;
}

void init()
{
	fac[0] = 1;
	REP(i, 1, maxlen - 1) fac[i] = 1ll * fac[i-1] * i % MOD;
	calc_inv(1 << 18 - 1, fac, ans);
	REP(i, 1, maxn-1) ans[i] = (-ans[i] + MOD) % MOD;
}

int main()
{
#ifdef CraZYali
	freopen("1514.in", "r", stdin);
	freopen("1514.out", "w", stdout);
#endif
	init();
	int T = read<int>();
	while (T--) printf("%d\n", (ans[read<int>()] + MOD) % MOD);
	return 0;
}
