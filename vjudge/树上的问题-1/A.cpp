#define  REP(i, s, e) for(register int i = s; i <= e ; i++)
#define DREP(i, s, e) for(register int i = s; i >= e ; i--)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10000 + 10;

int m, n, k;

pair <int, int> a[maxn];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first > B.first || A.first == B.first && A.second > B.second;}

bool vis[maxn];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF)
	{
		REP(i, 1, n)
		{
			register int x, y;
			scanf("%d%d", &x, &y);
			a[i] = make_pair(x, y);
		}
		sort(a + 1, a + 1 + n, cmp);
		memset(vis, 0, sizeof(vis));
		register int ans = 0;
		REP(i, 1, n)
			DREP(j, a[i].second, 1)
			if (!vis[j])
			{
				vis[j] = 1;
				ans += a[i].first;
				break;
			}
		printf("%d\n", ans);
	}
	return 0;
}
