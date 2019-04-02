#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
const int maxn = 500000 + 10;

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

int fa[maxn], siz[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y)
	{
		cout << -1 << endl;
		exit(0);
	}
}

struct node
{
	int u, siz;
	long long w;
	node(){}
	node(int _u, int _siz, long long _w) : u(_u), siz(_siz), w(_w) {}
	bool operator < (node B) const {return w * B.siz > B.w * siz;}
};
__gnu_pbds::priority_queue <node> q;

int n, a[maxn];
long long w[maxn], ans;

signed main()
{
#ifdef CraZYali
	freopen("4437.in", "r", stdin);
	freopen("4437.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, n) uni(i, a[i] = read<int>());
	REP(i, 0, n) siz[fa[i] = i] = 1;
	REP(i, 1, n) q.push(node(i, 1, w[i] = read<int>()));
	while (!q.empty())
	{
		int u(q.top().u), Siz(q.top().siz);
		q.pop();
		if (siz[u = find(u)] ^ Siz) continue;
		if (siz[fa[u]] > siz[u])
		{
			fa[u] = find(a[u]);
			ans += w[u] * siz[fa[u]];
			w[fa[u]] += w[u];
			siz[fa[u]] += siz[u];
			if (fa[u]) q.push(node(fa[u], siz[fa[u]], w[fa[u]]));
		}
	}
	cout << ans << endl;
	return 0;
}
