#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <map>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
int base, MOD;
int power_pow(int b, int base = ::base)
{
	int ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
int n, m, ans;

pair <int, int> path[(int)1e6];
int top;
map <int, int> cnt;
void dfs(int x, int y)
{
	if (x > n || y > m) return;
	path[++top] = make_pair(x, y);
	if (x == n && y == m)
	{
		int res(0);
		REP(i, 2, top)
			if (path[i].first ^ path[i-1].first) res += path[i].second;
		cnt[res]++;
//		(ans += power_pow(res)) %= MOD;
//		REP(i, 1, top) printf("%d %d\n", path[i].first, path[i].second);
//		puts("--------");
		--top;
		return;
	}
	dfs(x + 1, y);
	dfs(x, y + 1);
	--top;
}

signed main()
{
#ifdef CraZYali
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);
#endif
	int T;
	cin >> T >> base >> MOD;
	for (n = 1; n <= 14; n++)
		for (m = n; m <= 14; m++)
		{
			ans = 0;
			cnt.clear();
			//		scanf("%lld%lld", &n, &m);
			dfs(0, 0);
			printf("%lld %lld\n", n, m);
			for (auto i : cnt) printf("%lld %lld\n", i.first, i.second);
			puts("==============");
			fflush(stdout);
			fprintf(stderr, "(%lld, %lld) is Done!\n", n, m);
		}
	return 0;
}
