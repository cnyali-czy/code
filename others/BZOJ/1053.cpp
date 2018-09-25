#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e9 + 5;

int prime[] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int n, Max;
long long ans;

void dfs(int x = 0, long long now = 1, int cnt = 1, int limit = 30)
{
	if (x == 10)
	{
		if (now > ans && cnt > Max)
		{
			ans = now;
			Max = cnt;
		}
		else if (now <= ans && cnt >= Max)
		{
			ans = now;
			Max = cnt;
		}
		return;
	}
	x++;
	long long temp = 1;
	REP(i, 0, limit)
	{
		dfs(x, now * temp, cnt * (i + 1), i);
		temp *= prime[x];
		if (now * temp > n) break;
	}
}

int main()
{
#ifdef CraZYali
	freopen("1053.in", "r", stdin);
	freopen("1053.out", "w", stdout);
#endif
	cin >> n;

	dfs();

	cout << ans;

	return 0;
}
