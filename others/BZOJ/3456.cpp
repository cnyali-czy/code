#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 1004535809, maxn = 130000 + 10, maxlen = 1 << 18;

inline int power_pow(int base, long long b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) ans = 1ll * ans * base % MOD;
		base = 1ll * base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int R[maxlen], len;
inline void NTT(int A[], int flag)
{
	REP(i, 1, len - 1) if (i < R[i]) swap(A[i], A[R[i]]);
	for (register int i = 1; i < len; i <<= 1)
	{
		register int wn = power_pow(3, (MOD - 1) / (i * 2));
		if (flag < 0) wn = inv(wn);
		for (register int k = 0; k < len; k += i << 1)
		{
			register int t = 1;
			for (register int l = 0; l < i; l++, t = 1ll * t * wn % MOD)
			{
				register int x(A[k + l]), y(1ll * t * A[k + l + i] % MOD);
				A[k + l] = (x + y) % MOD;
				A[k + l + i] = (x - y) % MOD;
			}
		}
	}
	if (flag < 0)
	{
		register int invN = inv(len);
		REP(i, 0, len - 1) A[i] = 1ll * A[i] * invN % MOD;
	}
}

int temp[maxlen], n, A[maxlen], B[maxlen], C[maxlen], fac[maxn];
void calc_inv(int lim)
{
	if (!lim) return C[0] = inv(A[0]), void();
	calc_inv(lim >> 1);
	len = lim + lim;
	REP(i, 0, len - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? lim : 0);
	copy(A, A + lim, temp);
	NTT(temp, 1);NTT(C, 1);
	REP(i, 0, len - 1) C[i] = C[i] * (2ll - 1ll * temp[i] * C[i] % MOD + MOD) % MOD;
	NTT(C, -1);
	REP(i, lim, len - 1) C[i] = 0;
}
int Inv[maxn];

int main()
{
#ifdef CraZYali
	freopen("3456.in", "r", stdin);
	freopen("3456.out", "w", stdout);
#endif
	cin >> n;
	fac[0] = Inv[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * fac[i-1] * i % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n - 1, 1) Inv[i] = 1ll * Inv[i+1] * (i+1) % MOD;
	A[0] = 1;
	REP(i, 1, n)
	{
		A[i] = 1ll * power_pow(2, 1ll * i * (i-1) >> 1) * Inv[i] % MOD;
		B[i] = 1ll * power_pow(2, 1ll * i * (i-1) >> 1) * Inv[i-1] % MOD;
	}
	calc_inv(1 << 17);
	len = 1 << 18;
	REP(i, 0, len - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? len / 2 : 0);
	NTT(B, 1);NTT(C, 1);
	REP(i, 0, len - 1) B[i] = 1ll * B[i] * C[i] % MOD;
	NTT(B, -1);
	cout << (1ll * B[n] * fac[n-1] % MOD + MOD) % MOD << endl;
	return 0;
}
