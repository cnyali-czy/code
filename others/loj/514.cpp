#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e4 + 10, inf = 1e9;

int a[maxn], n, ans[maxn], q;

int main()
{
#ifdef CraZYali
	freopen("514.in", "r", stdin);
	freopen("514.out", "w", stdout);
#endif
	cin >> n >> q;REP(i, 1, n) scanf("%d", a + i);
	REP(i, 0, n) ans[i] = -inf;
	REP(i, 1, n)
	{
		int s = 0;
		REP(j, i, n)
		{
			s += a[j];
			ans[j - i + 1] = max(ans[j - i + 1], s);
		}
	}
	DEP(i, n - 1, 0) ans[i] = max(ans[i], ans[i + 1]);
	while (q--) {int x;scanf("%d", &x);printf("%d\n", ans[x]);}
	return 0;
}
