#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10;

int n, k, a[maxn];
i64 f[maxn];

int main()
{
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	cin >> n >> k;REP(i, 1, n) scanf("%d", a + i);
	REP(i, 1, n)
	{
	}
	return 0;
}
