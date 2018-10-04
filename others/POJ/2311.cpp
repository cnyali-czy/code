#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 200 + 5;

int sg[maxn][maxn];

int dfs(int n, int m)
{
	if (sg[n][m] != -1) return sg[n][m];
	set <int> S;

	REP(i, 2, n - 2) S.insert(dfs(i, m) ^ dfs(n - i, m));
	REP(i, 2, m - 2) S.insert(dfs(n, i) ^ dfs(n, m - i));
	
	for (register int i = 0; ;i++)
		if (S.find(i) == S.end()) return sg[n][m] = i;
}

int m, n, k;

int main()
{
#ifdef CraZYali
	freopen("2311.in", "r", stdin);
	freopen("2311.out", "w", stdout);
#endif
	REP(i, 0, 201)
		REP(j, 0, 201)
			sg[i][j] = -1;
	while (scanf("%d%d", &n, &m) != EOF)
	{	
		if (dfs(n, m)) printf("WIN\n");
		else printf("LOSE\n");
	}
	
	return 0;
}
