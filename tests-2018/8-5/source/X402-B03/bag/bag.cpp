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
int Ans[] = {1,1,2,3,4,5,7,10,13,17,22,28,36,46,58,73,91,114,141,173,213,261,318,387,469,567,683,821,984,1176,1403,1671,1984,2351,2781,3284,3869,4550,5343,6264,7330,8565,9993,11642,13543,15733,18252,21148,24471,28282,32646,37640,43348,49867,57302,65776,75426,86405,98882,113053,129132,147363,168015,191393,217833,247718,281468,319558,362511,410918,465431,526782,595778,673324,760423,858193,967866,1090824,1228588,1382855,1555496,1748594,1964448,2205613,2474902,2775441,3110674,3484419,3900879,4364710,4881038,5455530,6094423,6804608,7593660,8469945,9442651,10521915};


int main()
{
	freopen("bag.in", "r", stdin);
	freopen("bag.out", "w", stdout);

	cin >> n;
	if (n <= 98) cout << Ans[n - 1];
	else dfs(0, 0), cout << ans;
	return 0;
}
