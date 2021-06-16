#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 3000 + 10;

int n, a[maxn], f[maxn][maxn];

signed main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%lld", a + i), a[i] -= i;
	static int id[maxn];
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [&](int x, int y) {return a[x] < a[y];});

	REP(i, 1, n) f[1][i] = max(0ll, a[1] - a[id[i]]);
	REP(i, 2, n) f[1][i] = min(f[1][i], f[1][i - 1]);

	REP(i, 2, n)
	{
		REP(j, 1, n) f[i][j] = abs(a[i] - a[id[j]]) + f[i - 1][j];
		REP(j, 2, n) f[i][j] = min(f[i][j], f[i][j - 1]);
	}
	cout << f[n][n] << endl;
	return 0;
}
