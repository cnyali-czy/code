#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxlen = 1 << 18, MOD = 998244353;

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
		if (b&1) ans = 1ll * ans * base % MOD;
		base = 1ll * base * base % MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int n, f[maxlen], R[maxlen], len;

void NTT(int a[], int flag)
{
	REP(i, 1, len-1) if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		int wn = power_pow(3, (MOD - 1) / (i << 1));
		if (flag < 0) wn = inv(wn);
		for (int k = 0; k < len; k += i << 1)
		{
			int w = 1;
			for (int l = 0; l < i;l++, w = 1ll * w * wn % MOD)
			{
				int x(a[k + l]), y(1ll * w * a[k + l + i] % MOD);
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

int Inv[maxlen], temp[maxlen];
void solve(int lim, int a[], int b[])
{
	if (!lim) return b[0] = inv(a[0]), void();
	solve(lim >> 1, a, b);
	len = lim + lim;
	REP(i, 1, len - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? lim : 0);
	copy(a, a + lim, temp);
	NTT(temp, 1);NTT(b, 1);
	REP(i, 0, len - 1) b[i] = 1ll * (2ll - 1ll * temp[i] * b[i] % MOD) % MOD * b[i] % MOD;
	NTT(b, -1);
	REP(i, lim, len - 1) b[i] = 0;
}

int main()
{
#ifdef CraZYali
	freopen("4238.in", "r", stdin);
	freopen("4238.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 0, n - 1) f[i] = read<int>();
	solve(1 << 17, f, Inv);
	REP(i, 0, n - 1) printf("%d%c", (Inv[i] + MOD) % MOD, i == n - 1 ? '\n' : ' ');
	return 0;
}
