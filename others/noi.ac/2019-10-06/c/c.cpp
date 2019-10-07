#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50 + 5, maxc = 100 + 5, maxN = maxn * maxc, MOD = 1e9 + 7;

int n, c[maxn], N, a[maxN];

int siz[maxN], fa[maxN];
inline void init()
{
	REP(i, 0, N) siz[fa[i] = i] = 1;
}
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y)
{
	if ((x = find(x)) == (y = find(y))) return;
	siz[fa[x] = y] += siz[x];
}

int main()
{
#ifdef CraZYali
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%d", c + i);
		REP(j, 1, c[i]) a[N++] = i;
	}
	register int ans(0);
	do
	{
		init();
		REP(i, 0, N - 1)
			if (a[i] == a[(i + N - 1) % N]) uni(i, (i + N - 1) % N);
		int res(1);
		REP(i, 0, N - 1) if (find(i) == i)
			(res *= siz[i]) %= MOD;
		(ans += res) %= MOD;
	}while (next_permutation(a, a + N));
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
