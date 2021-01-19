#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353;

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int n, m, a[maxn], b[maxn];

int fac[maxn], invs[maxn], Inv[maxn];
void init(int n)
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = i * fac[i - 1] % MOD;
		invs[i] = (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = invs[i] * Inv[i - 1] % MOD;
	}
}
int C(int n, int m) {return n < m || m < 0 ? 0 : fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int work(int sx, int sy)
{
	if ((sx > n) != (sy > m)) return 0;
	if (sx > n || sy > m) return 1;
	int res = 0;
	int w = min(a[sx], b[sy]), tx = sx - 1, ty = sy - 1;
	while (tx < n && a[tx + 1] == w) tx++;
	while (ty < m && b[ty + 1] == w) ty++;
	int A = tx - sx + 1, B = ty - sy + 1;
	int N = n - sx + 1, M = m - sy + 1;
	const int v = inv(w) * (w - 1) % MOD;
	REP(i, 0, A)
		(res += C(A, i) * (i & 1 ? -1 : 1) * power_pow(v, M * i) % MOD * power_pow(1 - power_pow(v, N - i), B)) %= MOD;
	res = res * power_pow(w, A * M + B * N - A * B) % MOD;
	return res * work(tx + 1, ty + 1) % MOD;
}

signed main()
{
#ifdef CraZYali
	freopen("J.in", "r", stdin);
	freopen("J.out", "w", stdout);
#endif
	cin >> n >> m;init(max(n, m));
	REP(i, 1, n) scanf("%lld", a + i);sort(a + 1, a + 1 + n);
	REP(i, 1, m) scanf("%lld", b + i);sort(b + 1, b + 1 + m);
	cout << (MOD + work(1, 1)) % MOD << endl;
	return 0;
}
