#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 3000 + 10;

inline int read() {int x;scanf("%d", &x);return x;}

vector <int> G[maxn];
inline void add(int x, int y) {G[x].emplace_back(y);G[y].emplace_back(x);}

int n, a[maxn];

bool f[maxn];
void dfs(int x, int fa = 0)
{
	f[x] = 0;
	for (int y : G[x]) if (y ^ fa)
	{
		dfs(y, x);
		if (a[x] > a[y]) f[x] |= (!f[y]);
	}
}
int main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	n = read();
	REP(i, 1, n) a[i] = read();
	REP(i, 2, n) add(read(), read());
	REP(i, 1, n)
	{
		dfs(i);
		if (f[i]) printf("%d ", i);
	}
	return 0;
}
