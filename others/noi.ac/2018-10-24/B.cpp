#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 2000 + 10, maxm = 4000 + 10;
int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

int pre[maxn], low[maxn], dfs_clock;
vector <int> bcc[maxn];
int bccno[maxn], bcccnt;
stack<pair <int, int> >s;

void dfs(int u, int fa = -1)
{
	low[u] = pre[u] = ++dfs_clock;
	for (register int i = bg[u]; i; i = ne[i])
		if (!pre[to[i]])
		{
			s.push(make_pair(u, to[i]));
			dfs(to[i], u);
			chkmin(low[u], low[to[i]]);
			if (low[to[i]] >= pre[u])
			{
				bcccnt++;
				while (!s.empty())
				{
					register int A[2];A[0] = s.top().first;A[1] = s.top().second;
					s.pop();
					REP(j, 0, 1)
						if (bccno[A[j]] ^ bcccnt) bcc[bccno[A[j]] = bcccnt].push_back(A[j]);
					if (A[0] == u && A[1] == to[i]) break;
				}
			}
		}
		else if (to[i] ^ fa && pre[to[i]] < pre[u])
		{
			s.push(make_pair(u, to[i]));
			chkmin(low[u], pre[to[i]]);
		}
}

int ans = 1ll << 60ll;
bool vis[maxn];
void pick(int x)
{
	if (x == n)
	{
		int res = 0;
		REP(X, 1, n)
			if (vis[X])
				for (register int i = bg[X]; i ; i = ne[i])
					if (vis[to[i]] && X < to[i]) res += w[i];
		REP(X, 1, n)
			if (!vis[X])
				for (register int i = bg[X] ; i ; i = ne[i])
					if (!vis[to[i]] && X < to[i]) res += w[i];
		chkmin(ans, res);
		return;
	}
	x++;
	vis[x] = 1;
	pick(x);
	vis[x] = 0;
	pick(x);
}

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}
	REP(i, 1, n) if (!pre[i]) dfs(i);
	REP(i, 1, bcccnt)
		if (bcc[i].size() >= 13)
		{
			cout << "cycle\n";
			int size = bcc[i].size() - 1;
			cout << size + 1 << endl;
			sort(bcc[i].begin(), bcc[i].end());
			REP(j, 0, size) printf("%lld ", bcc[i][j]);
			return 0;
		}
	pick(0);
	cout << "cut\n"<<ans;
	return 0;
}
