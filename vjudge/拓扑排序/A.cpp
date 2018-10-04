#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 500 + 10, maxm = maxn * maxn;

template <typename T> inline T read()
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

int in[maxn], ans[maxn];
bool G[maxn][maxn], vis[maxn];

void solve()
{
	REP(i, 1, n)
		REP(j, 1, n)
			if (!in[j])
			{
				in[j]--;
				ans[i] = j;
				REP(k, 1, n)
					if (G[j][k]) in[k]--;
				break;
			}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) != EOF)
	{
		REP(i, 1, n)
			REP(j, 1, n)
				G[i][j] = 0;
		REP(i, 1, n) in[i] = 0;
		while (m --> 0)
		{
			register int x = read<int>(), y = read<int>();
			if (G[x][y] == 0) in[y]++;
			G[x][y] = 1;
		}
		REP(i, 1, n) G[i][i] = 0;
		solve();
		REP(i, 1, n) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	}
	
	return 0;
}
