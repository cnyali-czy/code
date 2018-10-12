#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000 + 10, maxm = 2000 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k;

bool a[maxn][maxm];

int Left[maxn][maxm], Right[maxn][maxm], up[maxn][maxm];

int main()
{
#ifdef CraZYali
	freopen("1169.in", "r", stdin);
	freopen("1169.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
		REP(j, 1, m)
		{
			a[i][j] = read<int>();
			up[i][Left[i][j] = Right[i][j] = j] = 1;
		}

	REP(i, 1, n)
		REP(j, 2, m) 
			if (a[i][j] ^ a[i][j-1]) Left[i][j] = Left[i][j-1];
	REP(i, 1, n)
		DREP(j, m - 1, 1)
			if (a[i][j] ^ a[i][j+1]) Right[i][j] = Right[i][j+1];

	int ans1 = 0, ans2 = 0;

	REP(i, 1, n)
		REP(j, 1, m)
		{
			if (i > 1 && a[i][j] ^ a[i-1][j])
			{
				up[i][j] = up[i-1][j] + 1;
				k--;
				chkmax(Left[i][j], Left[i-1][j]);
				chkmin(Right[i][j], Right[i-1][j]);
			}
			chkmax(ans1, up[i][j] * (Right[i][j] - Left[i][j] + 1));
			chkmax(ans2, min(up[i][j], Right[i][j] - Left[i][j] + 1) * min(up[i][j], Right[i][j] - Left[i][j] + 1));
		}

	cout << ans2 << endl << ans1;
	return 0;
}
