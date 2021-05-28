#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
inline int read() {int x;scanf("%d", &x);return x;}

const int maxn = 1e5 + 10, maxm = 2e5 + 10;

int n, m;
vector <int> G[maxn];
vector <int> fk[2333];
inline int id(int x, int y) {return (x - 1) * n + y;}
int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	n = read();m = read();
	REP(i, 1, m)
	{
		int x = read(), y = read();
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	REP(a, 1, n) for (int c : G[a])
		REP(b, 1, n) for (int d : G[b])
			fk[id(a, b)].emplace_back(id(c, d));
	REP(x, 1, id(n, n)) for (int y : fk[x]) if (x < y) printf("%d %d\n", x, y);
	return 0;
}
