#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 50 + 5;

int n;
long long dp[maxn][maxn][maxn][maxn];
char s[maxn];
long long dfs(int cur, int x, int y, int z)
{
	if (cur == n) return x == y && !z;
	long long &ans = dp[++cur][x][y][z];
	if (ans != -1) return ans;
	ans = 0;
	if (s[cur] == 'S') ans = dfs(cur, x+1, y, z+1) + (x ? dfs(cur, x - 1, y + !z, z - !!z) : 0);
	else ans = (x ? dfs(cur, x - 1, y, z + 1) : 0) + dfs(cur, x + 1, y + !z, z - !!z);
	return ans;
}
int main()
{
#ifdef CraZYali
	freopen("2461.in","r",stdin);
	freopen("2461.out","w",stdout);
#endif
	int Case;
	cin >> Case;
	while (Case--)
	{
		memset(dp, -1, sizeof(dp));
		scanf("%s", s + 1);
		n = strlen(s + 1);
		printf("%lld\n", dfs(0, 0, 0, 0));
	}
	return 0;
}
