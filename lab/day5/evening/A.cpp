#define REP(i, s, e) for (int i = s; i <= e ;i++)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>
#define double long double
#define int long long

using namespace std;
const int maxn = 1e6 + 10, maxL = 4200000;

int n, ans, a[maxn], b[maxn], cnt[3000005];
int s[3000005];
void add(int x)
{
	while (x <= 3000001)
	{
		s[x]++;
		x += x & -x;
	}
}
int sum(int x)
{
	int res = 0;
	while (x > 0)
	{
		res += s[x];
		x -= x & -x;
	}
	return res;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%lld", a + i), a[i]++;
	REP(i, 1, n) scanf("%lld", b + i), b[i]++;
	if (n <= 2000)
	{
		REP(i, 1, n)
			REP(j, 1, n) 
			ans += floor(sqrt(abs(a[i] - b[j])));
	}
	else
	{
		REP(i, 1, n) cnt[a[i]]++;
		REP(i, 1, n) add(b[i]);
		REP(A, 1, 3000001)
			if (cnt[A])
				REP(C, 1, 1732)
				{
					int l, r;
					l = A - C * C - C * 2, r = A - C * C;
					if (max(l, 1ll) <= min(r, 3000001ll))
					{
						chkmax(l, 1ll);chkmin(l, 3000001ll);
						chkmax(r, 1ll);chkmin(r, 3000001ll);
						ans += C * cnt[A] * (sum(r) - sum(l-1));
					}
					l = A + C * C, r = A + C * C + C * 2;
					if (max(l, 1ll) <= min(r, 3000001ll))
					{
						chkmax(l, 1ll);chkmin(l, 3000001ll);
						chkmax(r, 1ll);chkmin(r, 3000001ll);
						ans += C * cnt[A] * (sum(r) - sum(l-1));
					}
				}
	}
	cout << ans << endl;
	return 0;
}
