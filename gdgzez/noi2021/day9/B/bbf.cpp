#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxk = 1e4 + 10;

int k, p;i64 m;
int f[maxk], g[maxk];

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("bbf.out", "w", stdout);
#endif
	cin >> k >> m >> p;
	const int MOD = p;
	f[1] = 1;
	REP(i, 1, m)
	{
		int sum = 0;
		REP(j, 0, k - 1)
		{
			g[j] = f[j];f[j] = 0;
			sum += g[j];
		}
		DEP(j, k - 1, 1) f[j] = g[j - 1];
		f[0] = sum % MOD;
		cout << sum % MOD << ' ' ;
	}
	int ans = 0;
	REP(i, 0, k - 1) ans += f[i];
	cout << ans % MOD << endl;
	return 0;
}

