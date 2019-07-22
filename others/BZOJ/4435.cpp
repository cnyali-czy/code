#define REP(i, s, e) for (int i = s; i <= e ; i++)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 3000 + 10, maxm = 4500 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, m, del;
int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}

int dfn[maxn], low[maxn], dfs_clock, cnt;
bool isbridge[maxm], vis[maxn];
const unsigned long long P = 1e9+9;
unsigned long long Hash[maxn];
int belong[maxn], s[maxn], top, bcc;
vector <int> bbb[maxn];
void tarjan(int u)
{
	dfn[u] = low[u] = ++dfs_clock;
	s[++top] = u;
	for (int i = bg[u]; i ; i = ne[i])
		if ((i >> 1) ^ del)
			if (!dfn[to[i]])
			{
				tarjan(to[i]);
				chkmin(low[u], low[to[i]]);
				if (low[to[i]] >= dfn[u])
				{
					isbridge[i >> 1] = 1;
					bcc++;
					if (!vis[u] && del)
					{
						vis[u] = 1;
						Hash[u] = Hash[u] * P + bcc;
						bbb[u].push_back(bcc);
					}
					while (1)
					{
						int x = s[top--];
						if (!vis[x] && del)
						{
							Hash[x] = Hash[x] * P + bcc;
							vis[x] = 1;
							bbb[x].push_back(bcc);
						}
						if (x == to[i]) break;
					}
				}
			}
			else chkmin(low[u], dfn[to[i]]);
}
void dfs(int u)
{
	belong[u] = cnt;
	for (int i = bg[u]; i ; i = ne[i])
		if (!isbridge[i >> 1] && !belong[to[i]]) dfs(to[i]);
}
void clear()
{
	REP(i, 1, n) dfn[i] = low[i] = vis[i] = 0;
	dfs_clock = top = bcc = 0;
}
int ans;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4435.in", "r", stdin);
	freopen("4435.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);add(y, x);
		uni(x, y);
	}
	REP(i, 1, n) if (!dfn[i]) tarjan(i);
	REP(i, 1, n) if (!belong[i])
	{
		cnt++;
		dfs(i);
	}
	clear();
	for (del = 1; del <= m; del++, clear())
		REP(i, 1, n)
		{if (!dfn[i]) tarjan(i);
			if(top)cout<<"FK\n";
			clear();
		}
	REP(i,1,n)printf("%d%c",belong[i],i==n?'\n':' ');puts("==========");
	REP(i,1,n)
	{
		printf("%llu:\t",Hash[i]);
		REP(j,0,(int)bbb[i].size()-1)printf("%d%c",bbb[i][j],j==(int)bbb[i].size()-1?'\n':' ');
	}
	REP(a, 1, n)
		REP(b, a + 1, n)
		if (find(a) ^ find(b)) continue;
		else if (belong[a] ^ belong[b])cout<<1<<endl, ans += 1;
		else if (Hash[a] != Hash[b])cout<<2<<endl, ans += 2;
		else cout<<3<<endl,ans += 3;
	cout << ans << endl;
	return 0;
}
