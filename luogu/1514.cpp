#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 500 + 5, maxm = maxn;

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

int n, m, k;
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool vis[maxn][maxm], can[maxm], reach[maxm][maxm];
int a[maxn][maxm];

void dfs(int x, int y)
{
	if (x == n)
	{
		can[y] = 1;
		reach[k][y] = 1;
	}
	REP(i, 0, 3)
	{
		register int tx = x + d[i][0];
		register int ty = y + d[i][1];
		if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
		if (vis[tx][ty] || a[tx][ty] >= a[x][y]) continue;
		vis[tx][ty] = 1;
		dfs(tx, ty);
	}
}

pair <int, int> seg[maxm];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first || A.first == B.first && A.second < B.second;}

int main()
{
#ifdef CraZYali
	freopen("1514.in", "r", stdin);
	freopen("1514.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
		REP(j, 1, m)
		a[i][j] = read<int>();

	for (k = 1; k <= m ; k++)
		if (a[1][k] >= a[1][k-1])
		{
			memset(vis, 0, sizeof(vis));
			vis[1][k] = 1;
			dfs(1, k);
		}

	register int nocnt = 0;
	REP(i, 1, m)
		if (!can[i]) nocnt++;
	if (nocnt) printf("0\n%d", nocnt);
	else
	{
		REP(i, 1, m)
		{
			seg[i] = make_pair(m + 1, m + 1);
			REP(j, 1, m)
				if (reach[i][j])
				{
					seg[i].first = j;
					break;
				}
			DREP(j, m, 1)
				if (reach[i][j])
				{
					seg[i].second = j;
					break;
				}
		}
		sort(seg + 1, seg + 1 + m, cmp);
		int M = m;
		while (seg[m].first == M + 1) m--;
		int lastsec = 1;
		while (lastsec < m && seg[lastsec + 1].first == seg[lastsec].first) lastsec++;
		int last = seg[lastsec].second, ans = 1;
		REP(i, lastsec + 1, m - 1)
			if (seg[i + 1].first > last + 1)
			{
				last = seg[i].second;
				ans++;
			}

		printf("1\n%d", ans + (last != M));
	}
	return 0;
}
