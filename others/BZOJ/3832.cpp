#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
const int maxn = 500000 + 10, maxm = 1000000 + 10;

vector <int> G[maxn], rG[maxn];
int deg[maxn];

inline void add(const int &x, const int &y)
{
	deg[y]++;
	G[x].push_back(y);
	rG[y].push_back(x);
}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

int Q[maxn], head, tail, dis[maxn], rdis[maxn];
inline void topsort()
{
	head = 1;
	REP(i, 1, n) if (!deg[i]) Q[++tail] = i;
	while (head <= tail)
	{
		register const int u(Q[head++]);
		for (register int v : G[u])
			if (!--deg[v]) Q[++tail] = v;
	}
}
inline void getdis()
{
	REP(i, 1, n)
	{
		register int u = Q[i];
		chkmax(dis[u], 1);
		for (register int v : G[u])
			chkmax(dis[v], dis[u] + 1);
	}
}
inline void getrdis()
{
	DREP(i, n, 1)
	{
		register int u = Q[i];
		chkmax(rdis[u], 1);
		for (register int v : G[u])
			chkmax(rdis[u], rdis[v] + 1);
	}
}
#include <set>
namespace Heap
{
	multiset <int> S;
	inline int push(const int &val) {S.insert(-val);}
	inline int top()
	{
		return -*S.begin();
	}
	inline void erase(const int &val) {S.erase(S.find(-val));}
}

int main()
{
#ifdef CraZYali
	file("3832");
#endif
	cin >> n >> m;
	while (m--)
	{
		register int x(read<int>()), y(read<int>());
		add(x, y);
	}

	topsort();
	memset(dis, -1, sizeof(dis));
	memset(rdis, -1, sizeof(rdis));
	getdis();
	getrdis();
#ifdef CraZYali
	REP(i, 1, n) printf("%d%c", dis[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", rdis[i], i == n ? '\n' : ' ');
#endif
	Heap::push(0);
	REP(i, 1, n) Heap::push(rdis[i]);

	pair <int, int> ans(1e9, 1e9);

	REP(x, 1, n)
	{
		register int u = Q[x];
		Heap::erase(rdis[u]);
		for (register int v : rG[u])
			Heap::erase(dis[v] + rdis[u]);
		chkmin(ans, make_pair(Heap::top(), u));
		for (register int v : G[u])
			Heap::push(dis[u] + rdis[v]);
		Heap::push(dis[u]);
	}
	cout << ans.second << ' ' << ans.first - 1 << endl;
	return 0;
}
