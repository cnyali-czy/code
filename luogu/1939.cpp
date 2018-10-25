#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MOD = 1e9 + 7;

int b[][4] = 
{
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 1},
	{0, 1, 0, 0}
}, base[4][4], n;

signed main()
{
#ifdef CraZYali
	freopen("1939.in", "r", stdin);
	freopen("1939.out", "w", stdout);
#endif
	cin >> n;
	while (scanf("%lld", &n) != EOF)
		if (n <= 3) printf("1\n");
		else
		{
			int ans[2][4] = {{0, 0, 0, 0}, {0, 1, 1, 1}};
			REP(i, 1, 3) REP(j, 1, 3) base[i][j] = b[i][j];
			int times = n - 3;
			while (times)
			{
				if (times & 1)
				{
					//ans *= base
					int c[2][4] = {0};
					REP(i, 1, 1)
						REP(j, 1, 3)
						REP(k, 1, 3)
							c[i][j] = (c[i][j] + ans[i][k] * base[k][j] % MOD) % MOD;
					REP(i, 1, 1) REP(j, 1, 3) ans[i][j] = c[i][j];
				}
				//base = base * base
				int c[4][4] = {0};
				REP(i, 1, 3)
					REP(j, 1, 3)
						REP(k, 1, 3)
							c[i][j] = (c[i][j] + base[i][k] * base[k][j] % MOD) % MOD;
				REP(i, 1, 3) REP(j, 1, 3) base[i][j] = c[i][j];
				times >>= 1;
			}
			printf("%lld\n", ans[1][1]);
		}

	return 0;
}
