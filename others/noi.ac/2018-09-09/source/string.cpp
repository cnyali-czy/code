#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxlen = 60, maxm = 100 + 10, maxN = maxlen * maxlen * maxlen;

int in[maxN];
long double dp[maxN];

int bg[maxN];
vector <int> ne, to, v;
inline void add(int x, int y)
{
	if (to.empty()) to.push_back(0);
	to.push_back(y);
	if (ne.empty()) ne.push_back(0);
	ne.push_back(bg[x]);
	bg[x] = ne.size() - 1;
}

int m, n, k;

#define idof(a, b, c) (a + b * (n + 1) + c * (n + 1) * (n + 1))

char sa[maxlen], sb[maxlen];
int xa[maxm], xb[maxm], xc[maxm], xd[maxm];
int ya[maxm], yb[maxm], yc[maxm], yd[maxm];

long double siz[maxN];

long double C[maxlen][maxlen];

void init_c()
{
	C[1][1] = 1;
	REP(i, 2, n + 5)
		REP(j, 1, i + 5)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
}

long double CCC(int x, int y)
{
	if (x == 0 || y == 0) return 1;
	return C[x][y];
}

int pre[maxN], low[maxN], dfs_clock;
stack <int> s;
bool vis[maxN];

int belong[maxN], scc_cnt;

void dfs(int u)
{
	pre[u] = low[u] = ++dfs_clock;
	vis[u] = 1;
	s.push(u);
	for (register int i = bg[u]; i ; i = ne[i])
		if (!pre[to[i]])
		{
			dfs(to[i]);
			chkmin(low[u], low[to[i]]);
		}
		else if (vis[to[i]]) chkmin(low[u], low[to[i]]);
	if (pre[u] == low[u])
	{
		vis[u] = 0;
		belong[u] = ++scc_cnt;
		while (s.top() ^ u)
		{
			vis[s.top()] = 0;
			belong[s.top()] = scc_cnt;
			s.pop();
		}
		s.pop();
	}
}

vector <int> ord;
queue <int> q;

set <pair<int, int> > S;

vector <int> G[maxN];

long double Finalsize[maxN];

int main()
{
#ifdef CraZYali
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	cin >> n >> m;
	init_c();
	REP(i, 1, m)
	{
		scanf("%s %s\n", sa + 1, sb + 1);
		k = strlen(sa + 1);
		REP(j, 1, k)
			(sa[j] == 'A' ? xa : (sa[j] == 'B' ? xb : (sa[j] == 'C' ? xc : xd)))[i]++;
		REP(j, 1, k)
			(sb[j] == 'A' ? ya : (sb[j] == 'B' ? yb : (sb[j] == 'C' ? yc : yd)))[i]++;
	}

	int N = -1;


	for (register int a = 0 ; a <= n ; a++)
		for (register int b = 0; a + b <= n ; b++)
			for (register int c = 0 ; a + b + c <= n ;c++)
			{
				siz[idof(a, b, c)] = CCC(n, a) * CCC(n - a, b) * CCC(n - a - b, c);
				chkmax(N, idof(a, b, c));
				register int d = n - a - b - c;
				REP(i, 1, m)
					if (a >= xa[i] && b >= xb[i] && c >= xc[i] && d >= xd[i] && idof(a, b, c) ^ idof(a - xa[i] + ya[i], b - xb[i] + yb[i], c - xc[i] + yc[i]))
						add(idof(a, b, c), idof(a - xa[i] + ya[i], b - xb[i] + yb[i], c - xc[i] + yc[i]));
			}
	
	REP(i, 1, N)
		if (!pre[i]) dfs(i);


	register long double ans = 0;
	REP(i, 1, N) chkmax(ans, Finalsize[belong[i]] += siz[i]);

	REP(x, 1, N)
		for (register int i = bg[x]; i ; i = ne[i])
			if (belong[x] ^ belong[to[i]] && S.find(make_pair(belong[x], belong[to[i]])) == S.end())
			{
				S.insert(make_pair(belong[x], belong[to[i]]));
				G[belong[x]].push_back(belong[to[i]]);
				in[belong[to[i]]]++;
			}

	REP(i, 1, scc_cnt)
		if (!in[i])
		{
			q.push(i);
			dp[i] = Finalsize[i];
		}
	
	REP(i, 1, scc_cnt)
		for (register int j = 0; j < G[i].size(); j++)
			printf("%d %d\n", i, G[i][j]);

	while (!q.empty())
	{
		register int i = q.front();
		q.pop();
		v.push_back(i);
		for (int j = 0; j < G[i].size(); j++)
			if (in[G[i][j]])
			{
				in[G[i][j]]--;
				if (!in[G[i][j]]) q.push(G[i][j]);
			}
	}

	for (register int i = 0 ; i < v.size() ; i++)
	{
		register int now = v[i];
		for (register int j = 0; j < G[now].size() ; j++)
			dp[G[now][j]] = dp[now] + Finalsize[G[now][j]];
	}

	REP(i, 1, scc_cnt) chkmax(ans, dp[i]);
	printf("%.0LF", ans);
	
	return 0;
}
