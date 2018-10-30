#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200000 + 10, maxm = 200000 + 10, MOD = 10007;
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

int m, n, k, w[maxn];

int fa[maxn], depth[maxn], sum[maxn][2], Max[maxn][2];

//sum[0] : 子树的权值和
//sum[1] : 平方的和
void dfs(int x)
{
	Max[x][0] = Max[x][1] = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			if (w[to[i]] > Max[x][0])
			{
				Max[x][1] = Max[x][0];
				Max[x][0] = w[to[i]];
			}
			else chkmax(Max[x][1], w[to[i]]);
			sum[x][0] = (sum[x][0] + w[to[i]]) % MOD;
			sum[x][1] = (sum[x][1] + w[to[i]] * w[to[i]] % MOD) % MOD;
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			dfs(to[i]);
		}
}

int tot;

int main()
{
#ifdef CraZYali
	freopen("1351.in", "r", stdin);
	freopen("1351.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	REP(i, 1, n) w[i] = read<int>();

	depth[1] = 1;
	dfs(1);

	int _Max = -1;

	REP(i, 1, n) if (depth[i] > 2) tot = (tot + 2 * w[i] * w[fa[fa[i]]]) % MOD, chkmax(_Max, w[i] * w[fa[fa[i]]]);
	REP(i, 1, n) tot = (tot + sum[i][0] * sum[i][0] - sum[i][1]) % MOD, chkmax(_Max, Max[i][0] * Max[i][1]);
	cout << _Max << ' ' << tot;

	return 0;
}
