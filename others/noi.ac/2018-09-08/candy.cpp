#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;

long long m, n, k;
long long a[maxn], b[maxn];

int main()
{
#ifdef CraZYali
	freopen("candy.in", "r", stdin);
	freopen("candy.out", "w", stdout);
#endif
	cin >> n >> m;
	DREP(i, n, 1) scanf("%lld", a + i);
	DREP(i, n, 1) scanf("%lld", b + i);

	REP(i, 1, n) a[i] += a[i-1];
	REP(i, 1, n) b[i] += b[i-1];

	long long ans = 0;

	REP(i, 1, n)
	{
		register int l = 1, r = n, p = n + 1;
		while (l <= r)
		{
			register int mid = l + r >> 1;
			if (b[mid] < a[i]) l = mid + 1;
			else
			{
				if (b[mid] >= a[i]) chkmin(p, mid);
				r = mid - 1;
			}
		}
		if (p == n + 1) continue;
		chkmax(ans, min(a[i], b[p]) - (i + p) * m);
	}

	swap(a, b);
	REP(i, 1, n)
	{
		register int l = 1, r = n, p = n + 1;
		while (l <= r)
		{
			register int mid = l + r >> 1;
			if (b[mid] < a[i]) l = mid + 1;
			else
			{
				if (b[mid] >= a[i]) chkmin(p, mid);
				r = mid - 1;
			}
		}
		if (p == n + 1) continue;
		chkmax(ans, min(a[i], b[p]) - (i + p) * m);
	}

	cout << ans;
	return 0;
}
