#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10;

int n, a[maxn], dp[maxn][2];

int bit[maxn];
struct st
{
	int table[maxn][20];
	inline void init()
	{
		REP(i, 1, n) table[i][0] = a[i];
		REP(j, 1, 19)
			for (register int i(1); i + (1 << j) - 1 <= n; i++)
				table[i][j] = max(table[i][j-1], table[i + (1 << j-1)][j-1]);
	}
	inline int query(int l, int r)
	{
		register int k = bit[r - l + 1];
		return max(table[l][k], table[r - (1 << k) + 1][k]);
	}
}ST;

int sta[maxn][2], p1, p2;


int main()
{
#ifdef CraZYali
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	n = 5;	
	REP(i, 1, n) bit[i] = bit[i >> 1] + (i & 1);
	REP(i, 1, n) a[i] = i;
	do
	{
		REP(i,1,n)printf("%d%c",a[i],i==n?'\n':' ');
		//	ST.init();
		const int lim = (1 << n) - 1;
		int ans(1e9);
		REP(S, 0, lim)
		{
			p1 = p2 = 0;
			REP(i, 1, n)
				if (S & (1 << i - 1)) sta[++p1][0] = a[i];
				else sta[++p2][1] = a[i];
			REP(i, 1, p1) chkmax(sta[i][0], sta[i-1][0]);
			REP(i, 1, p2) chkmax(sta[i][1], sta[i-1][1]);
			int res(0);
			REP(i, 1, p1) res += sta[i][0];
			REP(i, 1, p2) res += sta[i][1];
			chkmin(ans, res);
		}
		REP(S, 0, lim)
		{
			p1 = p2 = 0;
			REP(i, 1, n)
				if (S & (1 << i - 1)) sta[++p1][0] = a[i];
				else sta[++p2][1] = a[i];
			REP(i, 1, p1) chkmax(sta[i][0], sta[i-1][0]);
			REP(i, 1, p2) chkmax(sta[i][1], sta[i-1][1]);
			int res(0);
			REP(i, 1, p1) res += sta[i][0];
			REP(i, 1, p2) res += sta[i][1];
			if (res == ans)
			{
				printf("1: ");
				REP(i,1,n)
					if (S & (1 << i - 1)) printf("%d ",a[i]);putchar(10);
				printf("1: ");
				REP(i,1,n)
					if (!(S & (1 << i - 1))) printf("%d ",a[i]);putchar(10);
				break;
			}
		}
		cout << ans << endl;
		puts("--------------");
	}
	while(next_permutation(a+1,a+1+n));
	return 0;
}
