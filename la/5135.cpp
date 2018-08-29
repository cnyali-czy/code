#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;
const int maxn = 50000 + 19, maxm = 50000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, k;

int pre[maxn], low[maxn], dfs_clock;
bool iscut[maxn];

int bccno[maxn], bcccnt, root;
vector <int> bcc[maxn];

stack <pair <int, int> > s;

void dfs(int u, int fa)
{
	pre[u] = low[u] = ++dfs_clock;
	int child = 0;
	for (register int i = bg[u]; i ; i = ne[i])
		if (!pre[to[i]])
		{
			s.push(make_pair(u, to[i]));
			child++;
			dfs(to[i], u);
			chkmin(low[u], low[to[i]]);
			if (pre[u] <= low[to[i]])
			{
				iscut[u] = 1;
				bcc[++bcccnt].clear();
				while (!s.empty())
				{
					if (bccno[s.top().first] ^ bcccnt)	bcc[bcccnt].push_back(s.top().first),	bccno[s.top().first] = bcccnt;
					if (bccno[s.top().second] ^ bcccnt)	bcc[bcccnt].push_back(s.top().second),	bccno[s.top().second] = bcccnt;
					if (s.top().first == u && s.top().second == to[i])
					{
						s.pop();
						break;
					}
					s.pop();
				}
			}
		}
		else if (to[i] ^ fa && pre[to[i]] < pre[u])
		{
			s.push(make_pair(u, to[i]));
			chkmin(low[u], pre[to[i]]);
		}
	if (u == root && child == 1) iscut[u] = 0;
}

void get_bcc()
{
	REP(i, 1, n) bccno[i] = iscut[i] = pre[i] = low[i] = 0;
	bcccnt = dfs_clock = 0;
	REP(i, 1, n)
		if (!pre[i]) dfs(root = i, 0);
}

int main()
{
#ifdef CraZYali
	freopen("5135.in", "r", stdin);
	freopen("5135.out", "w", stdout);
#endif
	register int Case = 0;
	while (scanf("%d", &m) * m)
	{
		n = -1;
		e = 1;
		memset(bg, 0, sizeof(bg));
		while (m --> 0)
		{
			register int x, y;
			scanf("%d%d", &x, &y);
			add(x, y);add(y, x);
			chkmax(n, x);chkmax(n, y);
		}
		get_bcc();
		long long ans1 = 0, ans2 = 1;
		REP(i, 1, bcccnt)
		{
			register int cut_cnt = 0;
			REP(j, 0, (int)(bcc[i].size()) - 1)
				if (iscut[bcc[i][j]]) cut_cnt++;
			if (cut_cnt == 1)
			{
				ans1++;
				ans2 *= (long long)(bcc[i].size() - cut_cnt);
			}
		}
		if (bcccnt == 1) {ans1 = 2;ans2 = bcc[1].size() * (bcc[1].size() - 1) / 2;}
		printf("Case %d: %lld %lld\n", ++Case, ans1, ans2);
	}
	
	return 0;
}
