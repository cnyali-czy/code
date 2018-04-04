#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 1000 + 10;

int m, n, k;

char s[maxn];
int chunks, dp[maxn][maxn];
bool vis[300];

int main()
{
#ifdef CraZYali
	freopen("11552.in", "r", stdin);
	freopen("11552.out", "w", stdout);
#endif
	int T;
	cin >> T;
	while (T --> 0)
	{
		scanf("%d %s", &k, s + 1);
		n = strlen(s + 1);
		memset(dp, 127, sizeof(dp));
		REP(i, 0, n / k - 1)
		{
			chunks = 0;
			memset(vis, 0, sizeof(vis));
			REP(j, i * k + 1 , (i + 1) * k)
				vis[s[j]] = 1;
			REP(j, 'a', 'z') chunks += vis[j];
			if (i == 0)
				REP(j, 1, k) dp[i][j] = chunks;
			else
			{
				REP(j, 1, k)
				{
					int now = i * k + j;
					REP(p, 1, k)
					{
						int temp = (i - 1) * k + p ;
						if (vis[s[temp]] && (s[now] ^ s[temp] || chunks == 1))
								chkmin(dp[i][j], dp[i - 1][p] + chunks - 1);
						else	chkmin(dp[i][j], dp[i - 1][p] + chunks); 
					}
				}
			}
		}
		int ans = 1e9;
		REP(i, 1, k)
			chkmin(ans, dp[n / k - 1][i]);
		printf("%d\n", ans);
	}

	return 0;
}

