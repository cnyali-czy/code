/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.02 18:31
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
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
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, W, a[maxn], mid;
long long already;

void dfs(int x, int fa = -1)
{
	already += a[x];
	if (already >= W) return;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] != fa && mid >= w[i])
		dfs(to[i], x);
}

bool judge(int mid)
{
	already = 0;
	dfs(1);
	return already >= W;
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> W;
	REP(i, 2, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	int l(0), r(1e9);
	while (l <= r)
	{
		mid = l + r >> 1;
		if (judge(mid)) r = mid - 1;
		else l = mid + 1;
	}
	cout << r + 1 << endl;
	return 0;
}
