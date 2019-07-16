#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/extc++.h>
#define int long long
#define chkmax(a, b) a = max(a, b)

using namespace std;
const int maxn = 100000 + 10, maxm = maxn;
int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int root, n, m, ans;
int fa[maxn], cost[maxn], lead[maxn];
__gnu_pbds::priority_queue <int> q[maxn];

void solve(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
	{
		solve(to[i]);
		q[x].join(q[to[i]]);
		cost[x] += cost[to[i]];
	}
	while (cost[x] > m)
	{
		cost[x] -= q[x].top();
		q[x].pop();
	}
	chkmax(ans, lead[x] * (int)q[x].size());
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("2809.in", "r", stdin);
	freopen("2809.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		scanf("%lld%lld%lld", fa + i, cost + i, lead + i);
		if (fa[i]) add(fa[i], i);
		else root = i;
		q[i].push(cost[i]);
	}
	solve(root);
	cout << ans << endl;
	return 0;
}
