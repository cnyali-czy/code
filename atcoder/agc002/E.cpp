#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

int n, a[maxn];
int main()
{
#ifdef CraZYali
	freopen("1999.in", "r", stdin);
	freopen("1999.out", "w", stdout);
#endif
	cin >> n;REP(i, 1, n) scanf("%d", a + i);
	sort(a + 1, a + 1 + n, greater <int> () );
	REP(i, 1, n) if (i + 1 > a[i + 1])
	{
		int j = 0;
		while (a[i + j + 1] == i) j++;
		puts((a[i] - i & 1) || (j & 1) ? "First" : "Second");
		return 0;
	}
	return 0;
}
