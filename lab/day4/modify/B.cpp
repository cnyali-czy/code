#define REP(i, s, e) for (register int i = s; i <= e ;i++)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6 + 10, MOD = 1e9 + 7;

int m, n, k;

bitset <maxn> notprime;
int p[maxn], x[maxn], p_cnt;
int fib[maxn], u[maxn], ans;
inline int mod(int x) {return x >= MOD ? x - MOD : x;}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		if (!notprime[i]) x[p[++p_cnt] = i] = i;
		REP(j, 1, p_cnt)
		{
			if (i * p[j] > n) break;
			notprime[i * p[j]] = 1;
			x[i * p[j]] = p[j];
			if (i % p[j] == 0) break;
		}
	}
	fib[1] = 1;
	REP(i, 2, n) fib[i] = mod(fib[i-1] + fib[i-2]);
	u[1] = 1;
	REP(i, 2, n)
		if (x[i] ^ x[i / x[i]]) u[i] = -u[i / x[i]];
	REP(i, 1, n)
		for (register int j = 1; i * j <= n; j++)
		ans += 1ll * u[j] * (n / i / j) * (m / i / j) % MOD * fib[i] % MOD, ans %= MOD;
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
