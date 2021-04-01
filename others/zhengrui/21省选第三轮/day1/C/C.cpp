#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int MOD = 1e9 + 7;

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}

int N, M, p, q, F[25];
int calc(int x)
{
	int res = 0;
	DEP(i, q, 0) res = (res * x + F[i]) % MOD;
	return res;
}

int P[233], Q[233], top;
void split(int x)
{
	top = 0;
	for (int i = 2; i * i <= x; i++) if (x % i == 0)
	{
		int k = 0;
		while (x % i == 0) x /= i, k++;
		++top;
		P[top] = i;Q[top] = k;
	}
	if (x > 1) ++top, P[top] = x, Q[top] = 1;
}

signed main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> N >> M >> p >> q;
	REP(i, 0, q + 1) scanf("%lld", F + i);

	int ans = 0;
	REP(g, 1, N)
	{
		int res = 0;
		REP(i, 1, N / g)
		{
			split(i);
			int cur = 1;
			REP(j, 1, top)
				(cur *= power_pow(Q[j] + 1, M) - power_pow(Q[j], M)) %= MOD;
			(res += cur * power_pow(i * g, p)) %= MOD;
		}
		(ans += calc(g) * res) %= MOD;
	}
	ans %= MOD;
	cout << ans << endl;

	return 0;
}
