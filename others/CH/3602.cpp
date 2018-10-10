#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long

using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10, MOD = 1e9 + 9;

int bg[maxn], ne[maxm], to[maxm], e;
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

int low[maxn], pre[maxn], dfs_clock;
stack <int> S;

int belong[maxn], size[maxn], cnt;
bool vis[maxn];

void dfs(int u)
{
	low[u] = pre[u] = ++dfs_clock;
	vis[u] = 1;
	S.push(u);
	for (register int i = bg[u]; i ; i = ne[i])
		if (!pre[to[i]])
		{
			dfs(to[i]);
			chkmin(low[u], low[to[i]]);
		}
		else if (vis[to[i]]) chkmin(low[u], pre[to[i]]);
	if (low[u] == pre[u])
	{
		belong[u] = ++cnt;
		vis[u] = 0;
		while (S.top() ^ u)
		{
			belong[S.top()] = cnt;
			vis[S.top()] = 0;
			S.pop();
		}
		S.pop();
	}
}

void init()
{
	REP(i, 1, cnt) size[i] = 0;

	e = 0;
	REP(i, 1, n) bg[i] = 0;

	REP(i, 1, n) belong[i] = pre[i] = low[i] = vis[i] = 0;
	cnt = 0;
	dfs_clock = 0;
}

void tarjan()
{
	REP(i, 1, n)
		if (!pre[i]) dfs(i);
}

void tarjan_test()
{
	cin >> n >> m;
	while (m --> 0)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);
	}
	tarjan();
	REP(i, 1, n)
		printf("%d%c", belong[i], i == n ? '\n' : ' ');
}

int l[maxn];

int power_pow(int a, int b)
{
	a %= MOD;a = (a + MOD) % MOD;
	int base = a, ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

int inv(int x) {return power_pow(x, MOD - 2);}
int F(int x) {return power_pow(x, x - 2);}

int Inv[maxn];

signed main()
{
#ifdef CraZYali
	freopen("3602.in", "r", stdin);
	freopen("3602.out", "w", stdout);
#endif
	register int T = read<int>();
	
	register int temp = 1;
	REP(i, 1, 100000)
	{
		temp = temp * i % MOD;
		Inv[i] = inv(temp);
	}

	while (T --> 0)
	{
		n = read<int>();
		
		init();
		REP(i, 1, n)
			add(l[i] = read<int>(), i);

		tarjan();
		REP(i, 1, n) size[belong[i]]++;
		int ans = 1;
		REP(i, 1, n - cnt) ans = ans * i % MOD;
		REP(i, 1, cnt)
			if (size[i] > 1) ans = ans * F(size[i]) % MOD * Inv[size[i] - 1] % MOD;
		printf("%lld\n", (ans + MOD) % MOD);
	}
	
	return 0;
}
