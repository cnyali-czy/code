#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
const int maxn = 1e5 + 10, maxm = maxn * 2; 

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

int x[maxm], y[maxm], de[maxn];

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

int id[maxn];

queue <int> q;
bool vis[maxn];

bool flag = 1;

void solve(int root)
{
	while (!q.empty()) q.pop();
	q.push(root);
	id[root] = 1;
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (id[to[i]] == -1)
			{
				if (id[x] == 1) id[to[i]] = 2;
				else id[to[i]] = 1;
				q.push(to[i]);
			}	
	}
	while (!q.empty()) q.pop();
	q.push(root);
	while (!q.empty())
	{
		register int x = q.front();
		vis[x] = 1;
		q.pop();
		if (id[x] == -1)
		{
			cout << -1;
			exit(0);
		}
		for (register int i = bg[x]; i ; i = ne[i])
			if (!vis[to[i]]) q.push(to[i]);
	}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) fa[i] = i, id[i] = -1;
	REP(i, 1, m)
	{
		x[i] = read<int>(), y[i] = read<int>();
		fa[find(x[i])] = find(y[i]);
		de[x[i]]++;de[y[i]]++;
		add(x[i], y[i]);add(y[i], x[i]);
	}

	REP(i, 1, n) if (find(i) == i) solve(i);
	REP(i, 1, n) printf("%d ", id[i]);

	return 0;
}
