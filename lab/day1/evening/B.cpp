#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define REP(i, s, e) for (int i = s; i <= e ; i++)
#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10, maxm = 200000 + 10, inf = (((1 << 30) - 1) << 1) + 1;

int n, m, S, T;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
void clear()
{
	REP(i, 1, n) bg[i] = 0;
	e = 0;
}
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
pair <pair <int, int>, int> E[maxm];
int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

bool vis[maxn];
int Min[maxn], Max[maxn];
int q[maxn], head, tail;

bool flag;int a, b;
bool better(int a, int b, int A, int B) {return 1ll * a * B > 1ll * A * b;}

double t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m) scanf("%d%d%d", &E[i].first.first, &E[i].first.second, &E[i].second);
	cin >> S >> T;
	while ((t + clock()) * 1. / CLOCKS_PER_SEC <= 0.95)
	{
		t = clock();
		clear();
		random_shuffle(E + 1, E + 1 + m);
		REP(i, 1, n) fa[i] = i;
		REP(i, 1, m)
		{
			int u(find(E[i].first.first)), v(find(E[i].first.second));
			if (u ^ v)
			{
				fa[u] = v;
				add(E[i].first.first, E[i].first.second, E[i].second);
				add(E[i].first.second, E[i].first.first, E[i].second);
			}
		}
		REP(i, 1, n) vis[i] = 0;
		vis[q[head = tail = 1] = S] = 1;
		Max[S] = -inf;Min[S] = inf;
		while (head <= tail)
		{
			int x = q[head++];
			for (int i = bg[x] ; i ; i = ne[i])
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					Max[to[i]] = max(Max[x], w[i]);
					Min[to[i]] = min(Min[x], w[i]);
					q[++tail] = to[i];
				}
		}
		if (!flag || better(a, b, Max[T], Min[T]))
		{
			flag = 1;
			a = Max[T];b = Min[T];
		}
		t = clock() - t;
	}
	int g = __gcd(a, b);
	a /= g;
	b /= g;
	if (b == 1) cout << a << endl;
	else cout << a << '/' << b << endl;
#ifndef ONLINE_JUDGE
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
