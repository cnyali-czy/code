#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 25;

int a[maxn], n, m;

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	long long s = 0;
	REP(i, 0, n - 1) cin >> a[i], s += a[i];
	if (s < m) return puts("1") * 0;
	int ans = 0;
	REP(S, 0, (1 << n) - 1)
	{
		long long s = 0;int  mi = 1e9;
		REP(j, 0, n - 1)
			if (S >> j & 1) s += a[j];
			else mi = min(mi, a[j]);
		if (s >= m) continue;
		if (s + mi >= m) ans++;
	}
	cout << ans << endl;
	return 0;
}
