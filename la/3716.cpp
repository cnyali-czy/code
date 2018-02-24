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
const int maxn = 150000 + 10;

int n, p;

#define node pair<int, int>
#define fa first
#define len second
inline bool cmp(node a, node b) {return a.fa > b.fa || a.fa == b.fa && a.len < b.len;}

node c[maxn];
char a[maxn], b[maxn];

int main()
{
#ifdef CraZYali
	freopen("3716.in", "r", stdin);
	freopen("3716.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &p) != EOF)
	{
		if (!n && !p) return 0;
		
		scanf("%s%s", a + 1, b + 1);
		int ans = 0, cnt = 0;
		c[0].fa = c[0].len = 0;
		REP(i, 1, n)
		{
			cnt += a[i] != b[i];
			c[i].fa = cnt * 100 - (c[i].len = i) * p;
		}
		sort(c, c + 1 + n, cmp);
		int j = c[0].len;
		REP(i, 1, n)
			if (j < c[i].len) chkmax(ans, c[i].len - j);
			else j = c[i].len;
		if (ans) printf("%d\n", ans);
		else printf("No solution.\n");
	}
}
