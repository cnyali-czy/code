#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 4000000 + 10, maxm = 6000000 + 10;
const long long inf = 1ll << 60ll;

int S, T;

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
	Graph() {e = 1;}
	void add(int x, int y, int z, bool mode = 1)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
		if (mode) add(y, x, z, 0);
	}
	long long dis[maxm];
	priority_queue <pair<long long, int> > Q;
	void dij()
	{
		REP(i, 0, T) dis[i] = inf;
		Q.push(make_pair(dis[S] = 0, S));
		while (!Q.empty())
		{
			register int x = Q.top().second;
			register long long dist = -Q.top().first;
			Q.pop();
			if (dist > dis[x]) continue;
			for (register int i = bg[x]; i ; i = ne[i])
				if (dis[to[i]] > dist + w[i])
					Q.push(make_pair(-(dis[to[i]] = dist + w[i]), to[i]));
		}
	}
}G1, G2;

vector <int> V;
bool cmp(int a, int b) {return G1.w[a] < G1.w[b];}

int m, n, k;

void build()
{
	S = G1.e + 1;T = G1.e + 2;

	REP(x, 1, n)
	{
		vector <int>().swap(V);
		for (register int i = G1.bg[x] ; i ; i = G1.ne[i]) V.push_back(i);
		sort(V.begin(), V.end(), cmp);
		register int siz = V.size() - 1;
		REP(j, 0, siz)
		{
			G2.add(V[j], V[j] ^ 1, G1.w[V[j]], 0);
			if (x == 1) G2.add(S, V[j], G1.w[V[j]], 0);
			if (G1.to[V[j]] == n) G2.add(V[j], T, G1.w[V[j]], 0);
			if (j < siz)
			{
				G2.add(V[j], V[j + 1], G1.w[V[j + 1]] - G1.w[V[j]], 0);
				G2.add(V[j + 1], V[j], 0, 0);
			}
		}
	}
}

template <typename T> T read()
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

int main()
{
#ifdef CraZYali
	freopen("illness.in", "r", stdin);
	freopen("illness.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		register int x(read<int>()), y(read<int>()), z(read<int>());
		G1.add(x, y, z);
	}

	build();
	G2.dij();
	cout << G2.dis[T];

	return 0;
}
