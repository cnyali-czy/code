/*
	Problem:	A.cpp
	Time:		2021-02-08 08:41
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 6e5 + 10, MOD = 998244353;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int fac[maxn], invs[maxn], Inv[maxn];
void init(const int N = maxn - 10)
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, N)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}
}
inline int C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int n, m, type;

inline int go(int a, int n, int b) // (0, a) -> (n, b)
{
	if ((b - a + n) & 1) return 0;
	if ((b - a + n) < 0) return 0;
	return C(n, b - a + n >> 1);
}

int tot = 0;

void dfs(int sgn, int l1, int l2, int cur, int n, int lst = -1)
{
	if (cur > n || cur < -n) return ;
	tot += sgn * C(n, (n - cur) >> 1);
	if (lst != 1) dfs(-sgn, l1, l2, 2 * l1 - cur, n, 1);
	if (lst != 2) dfs(-sgn, l1, l2, 2 * l2 - cur, n, 2);
}

inline int calc(int n, int lim1, int lim2)
{
	tot = 0;
	dfs(1, lim1, lim2, 0, n);
	return (tot % MOD + MOD) % MOD;
}
int work(int n, int m)
{
	int ans = 0;
	REP(x1, 1, m) ans += calc(n << 1, m + 1 - x1, -x1);
	return ans % MOD;
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	init();
	cin >> n >> m >> type;
	if (type == 0) cout << work(n, m) << endl;
	else REP(i, 1, n) printf("%lld\n", work(i, m));
	return 0;
}
