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
const int maxn = 100000 + 10, maxm = 100000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e; 
}

int m, n, root;

int pre[maxn], low[maxn], dfs_clock;
bool iscut[maxn];

void dfs(int u, int fa)
{
	low[u] = pre[u] = ++dfs_clock;
	int children = 0;
	for (register int i = bg[u]; i ;i = ne[i])
		if (!pre[to[i]])
		{
			children++;
			dfs(to[i], u);
			chkmin(low[u], low[to[i]]);
			if (low[to[i]] >= pre[u]) iscut[u] = 1;
		}
		else if (to[i] ^ fa) chkmin(low[u], pre[to[i]]);
	if (u == root && children == 1) iscut[u] = 0;
}

int main()
{
#ifdef CraZYali
	freopen("3388.in", "r", stdin);
	freopen("3388.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		register int x, y;
		x = read<int>();y = read<int>();
		add(x, y);add(y, x);
	}
	
	REP(i, 1, n)
		if (!pre[i]) dfs(root = i, 0);
	
	int cnt = 0;
	REP(i, 1, n) if (iscut[i]) cnt++;
	write(cnt);putchar(10);
	REP(i, 1, n) if (iscut[i]) write(i), putchar(' ');
	return 0;
}
