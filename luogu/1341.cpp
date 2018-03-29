#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 3600, maxm = 3600;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, k;

pair<int, int> a[maxn];

inline int get()
{
	register char c = getchar();
	while (!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))) c = getchar();
	return (int)c;
}

int degree[300];
bool vis[300];

void dfs(int x)
{
	cout << (char)x;
	vis[x] = 1;
	vector <int> V;
	for (register int i = bg[x]; i ; i = ne[i])
		if (!vis[to[i]]) V.push_back(to[i]);
	sort(V.begin(), V.end());
	int siz = V.size();
	for (int i = 0; i < siz;++i)
		if (!vis[V[i]])
		{
			vis[V[i]] = 1;
			dfs(V[i]);
		}
}

int main()
{
#ifdef CraZYali
	freopen("1341.in", "r", stdin);
	freopen("1341.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
		a[i].first = get(), a[i].second = get();
#ifdef CraZYali
	REP(i, 1, n)
		fprintf(stderr, "%c %c\n", a[i].first, a[i].second);
#endif
	REP(i, 1, n)
	{
		add(a[i].first, a[i].second);
		add(a[i].second, a[i].first);
		degree[a[i].first]++;
		degree[a[i].second]++;
	}
	int cnt = 0;
	REP(i, 1, n)
	{
		register char c;
		
		c = a[i].first;
		if (!vis[c])
		{
			vis[c] = 1;
			if (degree[c] & 1) cnt++;
		}
		
		c = a[i].second;
		if (!vis[c])
		{
			vis[c] = 1;
			if (degree[c] & 1) cnt++;
		}
	}
	if (cnt > 2)
	{
		cout << "No Solution";
		return 0;
	}
	else
	{
		memset(vis, 0, sizeof(vis));
		int Min = 1000;
		REP(i, 1, n)
			chkmin(Min, (int)min(a[i].first, a[i].second));
		REP(i, 1, n)
			if (a[i].first == Min)
				dfs(a[i].first);
			else if (a[i].second == Min)
				dfs(a[i].second);
	}
	return 0;
}
