#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

int main()
{
#ifdef CraZYali
	freopen("1257.in", "r", stdin);
	freopen("1257.out", "w", stdout);
#endif

	long long n, k, ans;
	cin >> n >> k;
	ans = n * k;

	for (register int i = 1, gx; i <= n; i = gx + 1)
	{
		gx = k / i ? min(k / (k / i), n) : n;
		ans -= k / i * (i + gx) * (gx - i + 1) >> 1;
	}

	cout << ans;

	return 0;
}
