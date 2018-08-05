#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, MOD = 998244353;

int m, n, k, ans;

int a[maxn];

inline void dfs(int x, int tt)
{
	if (tt > n) return;
	if (x > n) return;
	if (tt == n)
	{
		ans = (ans + 1) % MOD;
		return;
	}
	x++;
	DREP(i, x, 0)
		dfs(x, tt + (a[x] = i) * x);
}

int main()
{
	freopen("bag.in", "r", stdin);
	freopen("bag.out", "w", stdout);
	REP(i, 1, 51)
	{
		ans = 0;
		n = i;
		dfs(0, 0);
		cout << ans << ',';
	}
	return 0;
}
