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
const int maxn = 500000 + 10, maxm = 500000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, s, x, y;

int grand[maxn][20], depth[maxn];

void get_fa(int x)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			depth[to[i]] = depth[grand[to[i]][0] = x] + 1;
			get_fa(to[i]);
		}
}

int main()
{
#ifdef CraZYali
	freopen("3379.in", "r", stdin);
	freopen("3379.out", "w", stdout);
#endif
	cin >> n >> m >> s;
	REP(i, 2, n)
	{
		x = read<int>();
		y = read<int>();
		add(x, y);add(y, x);
	}

	depth[s] = 1;
	get_fa(s);

	int Max = log(n) / log(2);

	REP(j, 1, Max)
		REP(i, 1, n)
			grand[i][j] = grand[grand[i][j - 1]][j - 1];
	while (m --> 0)
	{
		x = read<int>();
		y = read<int>();
		if (depth[x] < depth[y]) swap(x, y);
		DREP(i, Max, 0)
			if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
		if (x == y) write(x);
		else
		{
			DREP(i, Max, 0)
				if (grand[x][i] ^ grand[y][i])
				{
					x = grand[x][i];
					y = grand[y][i];
				}
			write(grand[x][0]);
		}
		putchar(10);
	}
	return 0;
}
