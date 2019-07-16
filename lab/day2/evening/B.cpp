#define REP(i, s, e) for (int i = s; i <= e ; i++)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10, maxm = 50000 + 10;
int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int n, m, root = 1;

map <int, int> cnt[maxn], tag[maxn];
map <int, int> :: iterator it;
int fa[maxn];
void dfs(int x, int f =- 1)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ f) dfs(to[i], fa[to[i]] = x);
}
void pushdown(int x)
{
	if (tag[x].empty()) return;
	for (it = tag[x].begin(); it != tag[x].end(); it++)
		for (int i = bg[x]; i ; i = ne[i])
			if (to[i] ^ fa[x])
			{
				tag[to[i]][it -> first] += it->second;
				cnt[to[i]][it -> first] += it->second;
			}
	tag[x].clear();
}
void pushfa(int x)
{
	if (x != root) pushfa(fa[x]);
	pushdown(x);
}
int query(int v, int y, int z)
{
	int res = 0;
	for (it = cnt[v].begin(); it != cnt[v].end(); it++)
		if (((it -> first) ^ y) <= z) res += it -> second;
	return res;
}
void pushall(int x)
{
	pushdown(x);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x]) pushall(to[i]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	freopen("B.err", "w", stderr);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		add(x, y);add(y, x);
	}
	dfs(root);
	cin >> m;
	REP(M, 1, m)
	{
		int opt;scanf("%lld", &opt);
		if (opt == 1)
		{
			int v, x, k;
			scanf("%lld%lld%lld", &v, &x, &k);
			tag[v][x] += k;
			cnt[v][x] += k;
		}
		else if (opt == 2)
		{
			int v, y, z;
			scanf("%lld%lld%lld", &v, &y, &z);
			pushfa(v);
			printf("%lld\n", query(v, y, z));
		}
		else
		{
			pushall(root);
			int v;
			scanf("%lld", &v);
			dfs(root = v);
			fa[root] = 0;
		}/*
#ifndef ONLINE_JUDGE
		cerr<<M<<endl;
		REP(i,1,n)
			for(it=cnt[i].begin();it!=cnt[i].end();it++)fprintf(stderr,"%lld %lld %lld\n",i,it->first,it->second);fputs("============\n",stderr);
#endif
*/
	}
	return 0;
}
