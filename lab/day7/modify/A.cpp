#define REP(i, s, e) for (int i = s; i <= e ;i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNs1TION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <vector>
#define int long long

using namespace std;
const int maxn = 1e6 + 10, maxnode = 2e7 ;

int s1[maxn], s2[maxn], a[maxn], n, ans;
void add(int s[], int x, int val = 1)
{
	while (x <= n)
	{
		s[x] += val;
		x += x & -x;
	}
}
int sum(int s[], int x)
{
	int res(0);
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
	REP(i, 1, n)
	{
		scanf("%lld", a + i);
		a[i] = n - a[i] + 2;
	}
	int l = 1, r = n;
	while (l < r) swap(a[l++], a[r--]);
	REP(i, 1, n) 
	{
		int temp = sum(s1, a[i]-1);
		ans += temp * (temp - 1) / 2 - sum(s2, a[i] - 1);
		add(s1, a[i]);
		add(s2, a[i], sum(s1, a[i]) - 1);
	}
	cout << ans << endl;
	return 0;
}
