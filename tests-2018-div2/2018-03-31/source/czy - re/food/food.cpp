#define REP(i, s, e) for(register int i =  s; i <= e ;++i)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10;

long long m, n, k;

pair<long long, long long> a[maxn];

inline bool cmp(pair<long long, long long> A, pair<long long, long long> B)
{
	return A.first < B.first;
}

inline bool judge(long long Mid)
{
	long long x = Mid;
	REP(i, 1, n)
		if (x >= a[i].first) x += a[i].second + Mid;
		else return 0;
	return 1;
}

int main()
{
	freopen("food.in", "r", stdin);
	freopen("food.out", "w", stdout);
	cin >> n;
	REP(i, 1, n) scanf("%lld%lld", &a[i].first, &a[i].second);
	sort(a + 1, a + 1 + n, cmp);
	long long l(1), r(a[n].first), ans(a[n].first);
	while (l <= r)
	{
		long long mid = l + r >> 1;
		if (judge(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ans;
	return 0;
}
