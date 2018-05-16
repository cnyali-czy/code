#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

int f[maxn];
int find(int x) {return f[x] ^ x ? f[x] = find(f[x]) : x;}
inline void uni(int x, int y) {f[find(x)] = find(y);}

bool vis[maxn][2];
int DP[maxn][2];

int dp(int x, bool put = 0, int fa = -1)
{
	if (vis[x][put]) return DP[x][put];
	vis[x][put] = 1;
	int& ans = DP[x][put];
	ans = 2333;

	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] != fa) ans += dp(to[i], 1, x);
	if (!put && fa != -1) ans++;
	if (put || fa == -1)
	{
		int sum = 0;
		for (register int i = bg[x]; i ;i = ne[i])
			if (to[i] != fa) sum += dp(to[i], 0, x);
		if (fa != -1) sum++;
		ans = min(ans, sum);
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("10859.in", "r", stdin);
	freopen("10859.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();
		m = read<int>();
		REP(i, 1, n) f[i] = i;
		memset(vis, 0, sizeof(vis));
		memset(DP, 0, sizeof(DP));
		memset(bg, 0, sizeof(bg));
		e = 1;
		REP(i, 1, m)
		{
			int x(read<int>() + 1), y(read<int>() + 1);
			add(x, y);
			add(y, x);
			uni(x, y);
		}
		register int ans = 0;
		REP(i, 1, n)
			if (f[i] == i) ans += dp(i);
		printf("%d %d %d\n", ans / 2333, m - ans % 2333, ans % 2333);
	}

	return 0;
}
