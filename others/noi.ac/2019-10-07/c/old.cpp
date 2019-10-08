#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10;

int n, q, type, a[maxn];

namespace bf
{
	int sg[maxn][maxn], tmp1[maxn][maxn], tmp2[maxn][maxn];

	int SG(int l, int r)
	{
		if (sg[l][r] != -1) return sg[l][r];
		return sg[l][r] = (!SG(l + 1, r) || !SG(l, r - 1));
	}
	inline void work()
	{
		REP(i, 1, n) sg[i][i] = 1;

		REP(i, 1, n) tmp1[i][i] = 1;
		REP(i, 1, n)
			REP(j, i + 1, n)
			if (tmp1[i][j-1] != 1) break;
			else tmp1[i][j] = (a[j-1] <= a[j]); 
		REP(i, 1, n)
			REP(j, i + 1, n)
			if (tmp1[i][j-1] || tmp1[i+1][j]) sg[i][j] = 1;
		if (type == 2)
		{
			REP(i, 1, n) tmp2[i][i] = 1;
			REP(i, 1, n)
				REP(j, i + 1, n)
				if (tmp2[i][j-1] != 1) break;
				else tmp2[i][j] = (a[j-1] >= a[j]); 
			REP(i, 1, n)
				REP(j, i + 1, n)
				if (tmp2[i][j-1] || tmp2[i+1][j]) sg[i][j] = 1;
		}
		cin >> q;
		while (q--)
		{
			register int l, r;
			scanf("%d%d", &l, &r);
			if (tmp1[l][r] || tmp2[l][r]) printf("Bob\n");
			else printf("%s\n", SG(l, r) ? "Alice" : "Bob");
		}
		REP(i, 1, n)
			REP(j, 1, n)
			if (j>=i)
			printf("%d%c", SG(i,j),j==n?'\n':' ');
			else printf("  ");
	}
}

int main()
{
#ifdef CraZYali
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	cin >> n >> type;
	memset(bf::sg, -1, sizeof(bf::sg));
	REP(i, 1, n) scanf("%d", a + i);
	if (n <= 1000) bf::work();
	return 0;
}
