#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 2e5 + 10;

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m, ans;
int fa[maxn], siz[maxn], e[maxn];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void uni(int x, int y)
{
	fa[x] = y;
	siz[y] += siz[x];
	e[y] += e[x] + 1;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m;
	REP(i, 1, n) siz[fa[i] = i] = 1;
	while (m--)
	{
		int x(find(read<int>())), y(find(read<int>()));
		if (x == y) e[x]++;
		else uni(x, y);
	}
	REP(i, 1, n) if (i == find(i))
		ans += siz[i] - (siz[i] - e[i] & 1);
	cout << ans << endl;
	return 0;
}
