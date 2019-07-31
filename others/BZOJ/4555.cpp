#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100000 + 10, L = 18, len = 1 << L, MOD = 998244353;

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

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = 1ll * ans * base % MOD;
		base = 1ll * base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int n, R[len], invN = inv(len);
void NTT(int a[], int flag)
{
	REP(i, 1, len-1) if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		int T = power_pow(3, (MOD - 1) / (i * 2));
		for (int k = 0; k < len; k += (i << 1))
		{
			int t = 1;
			for (int l = 0; l < i;l++, t = 1ll * t * T % MOD)
			{
				int x(a[k + l]), y(1ll * t * a[k + l + i] % MOD);
				a[k + l] = (x + y) % MOD;
				a[k + l + i] = (x - y) % MOD;
			}
		}
	}
	if (flag < 0)
		REP(i, 0, len - 1) a[i] = 1ll * a[i] * invN % MOD;
}
int fac[maxn], Inv[maxn], f[len], g[len];

int main()
{
#ifdef CraZYali
	file("4555");
#endif
	REP(i, 1, len-1) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	cin >> n;
	fac[0] = Inv[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * fac[i-1] * i % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n-1, 1) Inv[i] = 1ll * Inv[i+1] * (i+1) % MOD;
	REP(i, 0, n) f[i] = (i & 1 ? -Inv[i] : Inv[i]);
	g[0] = 1;g[1] = n + 1;
	REP(i, 2, n) g[i] = 1ll * (power_pow(i, n + 1) - 1 + MOD) % MOD * Inv[i-1] % MOD * fac[i-2] % MOD * Inv[i] % MOD;
	NTT(f, 1);NTT(g, 1);
	REP(i, 0, len-1) f[i] = (1ll * f[i] * g[i] % MOD+MOD)%MOD;
	NTT(f, -1);
	REP(i, 0, len-1) f[i] = (f[i] + MOD) % MOD;
	reverse(f+1,f+len);
	int ans = 0, bin = 1;
	
	REP(i, 0, n) ans = (ans + 1ll * f[i] * fac[i] % MOD * bin % MOD) % MOD, bin = (bin << 1) % MOD;
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
