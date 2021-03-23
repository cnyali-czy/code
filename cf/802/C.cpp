#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5;

int n, k, a[maxn], c[maxn], ans;

int lst[maxn];

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n) scanf("%d", a + i);
	REP(i, 1, n) scanf("%d", c + i);
	REP(i, 1, n) ans += c[a[i]];

	REP(i, 1, n)
	{
	}

	cout << ans << endl;
	return 0;
}
