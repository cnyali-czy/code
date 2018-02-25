#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100, maxm = 100, maxk = 20;

int m, n, k, d[300][10];

char s[maxn][maxm];

int in[maxk], e[maxn][maxm];

#define inside(x, y) (1 <= x && x <= n && 1 <= y && y <= m)

queue <int> q;
bool die[maxn];

inline void init_d()
{
	d['>'][0] = 0;
	d['>'][1] = 1;
	d['<'][0] = 0;
	d['<'][1] = -1;
	d['^'][0] = -1;
	d['^'][1] = 0;
	d['v'][0] = 1;
	d['v'][1] = 0;
}

int X[maxk], Y[maxk];

int ans;
vector <int> G[maxk];
inline void dfs(int now, int al)
{
	if (al == k)
	{
		ans++;
		return;
	}
	int siz = G[now].size() - 1;
	REP(i, 0, siz)
		if (!die[G[now][i]]) in[G[now][i]]--;
		
	REP(i, 1, k)
		if (!in[i] && !die[i])
		{
			die[i] = 1;
			dfs(i, al + 1);
			die[i] = 0;
		}

	REP(i, 0, siz)
		if (!die[G[now][i]]) in[G[now][i]]++;
}

int main()
{
	freopen("cmdo.in", "r", stdin);
	freopen("cmdo.out", "w", stdout);
	cin >> n >> m;
	REP(i, 1, n)
		scanf("%s", s[i] + 1);
	REP(i, 1, n)
		REP(j, 1, m)
			if (s[i][j] ^ '.' && s[i][j] ^ '#')
			{
				e[i][j] = ++k;
				X[k] = i;Y[k] = j;
			}
	init_d();
	REP(i, 1, n)
		REP(j, 1, m)
			if (e[i][j])
			{
				int x = i, y = j;
				while (s[x][y] ^ '#')
				{
					x += d[s[i][j]][0];
					y += d[s[i][j]][1];
					if (inside(x, y) && e[x][y])
					{
						in[e[x][y]]++;
						G[e[i][j]].push_back(e[x][y]);
					}
					else if (!inside(x, y)) break;
				}
			}
	REP(i, 1, k)
		if (!in[i])
		{
			die[i] = 1;
			dfs(i, 1);
			die[i] = 0;
		}
	if (ans) printf("%d", ans);
	else printf("Impossible");
	return 0;
}
