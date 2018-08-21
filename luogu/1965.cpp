#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 100010;

long long power_pow(long long a, long long b, long long MOD)
{
	a %= MOD;
	register long long ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

long long x, m, n, k;

int main()
{
#ifdef CraZYali
	freopen("1965.in", "r", stdin);
	freopen("1965.out", "w", stdout);
#endif
	cin >> n >> m >> k >> x;
	long long t = power_pow(10, k, n);

	cout << (x + m * t % n) % n;

	return 0;
}

