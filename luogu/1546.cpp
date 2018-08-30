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

const int maxn = 100 + 5;

int m, n, k;
int G[maxn][maxn], d[maxn];

priority_queue <pair<int, int> >Q;
bool vis[maxn];

int main()
{
#ifdef CraZYali
	freopen("1546.in", "r", stdin);
	freopen("1546.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) REP(j, 1, n) scanf("%d", &G[i][j]);
	REP(i, 2, n) d[i] = 1e9;
	Q.push(make_pair(0, 1));
	register int ans = 0;
	while (!Q.empty())
	{
		register int dist = -Q.top().first;
		register int x = Q.top().second;
		Q.pop();
		if (dist > d[x] || vis[x]) continue;
		else
		{
			vis[x] = 1;
			ans += dist;
			REP(i, 1, n)
				if (!vis[i] && G[x][i] && d[i] > G[x][i]) Q.push(make_pair(-(d[i] = G[x][i]), i));
		}
	}
	cout << ans;
	return 0;
}
