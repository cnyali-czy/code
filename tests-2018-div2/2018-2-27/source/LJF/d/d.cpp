#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )

const int maxn = 100010;

int n, m, b[maxn], c[maxn], Begin[maxn], To[maxn], Next[maxn], e, W[maxn];

int ans = 2147483647;

void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

void dfs(int x, int t)
{
	if ( ans <= t ) return ;
	if ( x == n ) 
	{
		ans = t;
		return ;
	}
	if ( t % (b[x] + c[x]) > c[x] && t != 0 ) return ;
	dfs(x, t + 1);
	for ( int i = Begin[x]; i; i = Next[i] )
	{
		int u = To[i];
		dfs(u, t + W[i]);
	}
}

int main()
{
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
	scanf("%d", &n);
	REP(i, 0, n - 1) scanf("%d%d", &b[i], &c[i]);
	scanf("%d", &m);
	REP(i, 1, m)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	dfs(0, 0);
	printf("%d\n", ans);
	return 0;
}

