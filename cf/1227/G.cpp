#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 1000 + 10;

int n, a[maxn], c[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d", a + i);
	static int id[maxn];
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [&](int x, int y) {return a[x] > a[y];});
	REP(i, 1, n)
	{
		int x = a[id[i]];
		for (int j = n + 1 - (i - 1); x--;)
		{
			c[j][id[i]] = 1;
			j--;if (!j) j = n + 1;
		}
	}
	cout << n + 1 << endl;
	REP(i, 1, n + 1)
	{
		REP(j, 1, n) putchar(c[i][j] + 48);
		puts("");
	}
	return 0;
}
