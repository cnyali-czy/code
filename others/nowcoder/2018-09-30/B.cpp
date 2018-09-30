#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10, maxm = maxn;
const long long MOD = 1e9 + 7;

void exgcd(long long a, long long b, long long &x, long long &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

long long inv(long long x)
{
	register long long A, B;
	exgcd(x, MOD, A, B);
	return (A + MOD) % MOD;
}

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

int m, n, k, l, r, LOG;

int depth[maxn], grand[maxn][30];

void dfs(int x)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			dfs(to[i]);
		}
}

int getlca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0)
		if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	else
	{
		DREP(i, LOG, 0)
			if (grand[x][i] ^ grand[y][i])
			{
				x = grand[x][i];
				y = grand[y][i];
			}
		return grand[x][0];
	}
}

bool vis[maxn], vis1[maxn], vis2[maxn], vis3[maxn];

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> l >> r;
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);
		add(y, x);
	}

	LOG = log2(n);
	depth[1] = 1;
	dfs(1);
	/*
	   REP(j, 1, LOG)
	   REP(i, 1, n)
	   grand[i][j] = grand[grand[i][j-1]][j-1];
	   */

	/*
	   REP(x, 1, n)
	   {
	   REP(i, 1, n) vis[i] = 0;
	   vis[x] = 1;
	   register int y = x;
	   register int cnt = 1;
	   while (y ^ 1)
	   {
	   y = grand[y][0];
	   vis[y] = 1;
	   cnt++;
	   REP(u, 1, n)
	   {
	   register int Cnt = cnt;
	   register int v = u;
	   if (!vis[u]) Cnt++;
	   vis[u] = 1;

	   while (v != 1)
	   {
	   v = grand[v][0];
	   if (!vis[v]) Cnt++;
	   if (u == x && v == y) continue;
	   if (l <= Cnt - 1 && Cnt - 1 <= r) {ans++;if (ans >= MOD) ans %= MOD;}
	   cerr << u << ' ' << v <<  ' ' << x << ' ' << y << ' ' << Cnt << endl;
	   }
	   }
	   }
	   }
	   */

	register long long ans = 0 ;
	REP(x, 1, n)
		REP(y, x, n)
		REP(u, 1, n)
		REP(v, u, n)
		{
			REP(i, 1, n) vis1[i] = vis2[i] = vis3[i] = vis[i] = 0;
			if (x == u && y == v) continue;
			register int lca1 = getlca(x, y), lca2 = getlca(u, v);
			register int X = x, Y = y, U = u, V = v;
			vis1[X] = vis1[Y] = 1;
			vis2[U] = vis2[V] = 1;

			while (X ^ lca1) vis1[X = grand[X][0]] = 1;
			while (Y ^ lca1) vis1[Y = grand[Y][0]] = 1;
			while (U ^ lca2) vis2[U = grand[U][0]] = 1;
			while (V ^ lca2) vis2[V = grand[V][0]] = 1;
			REP(i, 1, n) vis[i] = vis1[i] & vis2[i];


			register int top, bot;
			register int Max = -1, Min = 1e9;

			REP(i, 1, n)
				if (vis[i])
				{
					if (depth[i] > Max)
					{
						Max = depth[i];
						bot = i;
					}
					if (depth[i] < Min)
					{
						Min = depth[i];
						top = i;
					}
				}
			/*
			   cerr << "---------------------\n";
			   REP(i, 1, n) if (vis[i]) cerr << i << ' ' ;cerr<<endl;
			   REP(i, 1, n) if (vis3[i]) cerr << i << ' ' ;cerr<<endl;
			   cerr << "---------------------\n";
			   */
			register int AAA = bot;
			vis3[AAA] = 1;
			while (AAA ^ top) vis3[AAA = grand[AAA][0]] = 1;
			register bool flag = 1;
			register int cnt = 0;
			REP(i, 1, n)
				if (vis[i] && !vis3[i] || !vis[i] && vis3[i])
				{
					flag = 0;
					break;
				}
				else if (vis[i] && vis3[i]) cnt++;
			
			ans += flag & (l <= cnt - 1 && cnt - 1 <= r);
			if (ans >= MOD) ans %= MOD;
			/*
			if (flag & (l <= cnt - 1 && cnt - 1 <= r) )
			{
				
				cout << "-------------\n";
				cout << "cnt = " << cnt << endl;
				cout << x <<  ' ' << y  <<  ' ' << u <<  ' ' << v << endl;
				REP(i, 1, n) if (vis1[i]) cout << i <<  ' ';cout<<endl;
				REP(i, 1, n) if (vis2[i]) cout << i <<  ' ';cout<<endl;
				cout << "-------------\n";
			}
			*/
		}


	cout << (long long)ans * inv(2) % MOD;

	return 0;
}
