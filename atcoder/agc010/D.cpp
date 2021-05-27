#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10;

int n, a[maxn];
bool calc()
{
	i64 sum = 0;
	REP(i, 1, n) sum += a[i] - 1;
	if (sum & 1) return 1;
	int cnt = 0;
	REP(i, 1, n) if (a[i] & 1) cnt++;
	if (cnt > 1) return 0;
	REP(i, 1, n) if (a[i] & 1)
	{
		if (a[i] == 1) return 0;
		a[i]--;
	}
	int g = a[1];
	REP(i, 2, n) g = __gcd(g, a[i]);
	REP(i, 1, n) a[i] /= g;
	return !calc();
}

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d", a + i);
	puts(calc() ? "First" : "Second");
	return 0;
}
