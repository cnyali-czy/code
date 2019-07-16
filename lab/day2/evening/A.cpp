#define REP(i, s, e) for (int i = s; i <= e; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#include <bits/extc++.h>
#define int long long

using namespace std;
const int maxn = 300000 + 10, maxm = maxn;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int depth[maxn], fa[maxn];
void pre(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			pre(to[i]);
		}
}

struct man
{
	int down, up, cost, id;
	man(){}
	man(int _down, int _up, int _cost, int _id) : down(_down), up(_up), cost(_cost), id(_id) {}
	bool operator < (man B) const {return cost > B.cost || cost == B.cost && depth[down] - depth[up] < depth[B.down] - depth[B.up] || cost == B.cost && depth[down] - depth[up] == depth[B.down] - depth[B.up] && id == B.id;}
};

__gnu_pbds :: priority_queue <man> q[maxn], del[maxn], temp;

int Id[maxn];
bool notleave[maxn];
int solve(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			notleave[x] = 1;
			solve(to[i]);
			q[x].join(q[to[i]]);
			del[x].join(del[to[i]]);
		}
	while (!del[x].empty() && del[x].top().id == q[x].top().id) q[x].pop(), del[x].pop();
	if (q[x].empty() && x > 1) {cout << -1;exit(0);}
	//temp=q[x];
	//while(!temp.empty()){printf("%lld %lld %lld\n", x, temp.top().cost, temp.top().id);temp.pop();}
	return Id[x] = (!q[x].empty() ? q[x].top().id : -1);
}
int n, m, cost[maxm];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		add(x, y);add(y, x);
	}
	pre(1);
	REP(i, 1, m)
	{
		int down, up;
		scanf("%lld%lld%lld", &down, &up, cost + i);
		q[down].push(man(down, up, cost[i], i));
		del[up].push(man(down, up, cost[i], i));
	}
	solve(1);
//	REP(i,1,n)cout<<Id[i]<<' ';cout<<endl;
	int ans = 0;
	REP(i,2,n)
		if(Id[fa[i]] != Id[i]) ans += cost[Id[i]];
	cout << ans << endl;
	return 0;
}
