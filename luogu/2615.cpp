#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 40;

int m, n, k;

int posx[maxn * maxn], posy[maxn * maxn];

int a[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("2615.in", "r", stdin);
	freopen("2615.out", "w", stdout);
#endif
	cin >> n;

	a[posx[1] = 1][posy[1] = n / 2 + 1] = 1;
	REP(i, 2, n * n)
		if (posx[i - 1] == 1 && posy[i - 1] != n) a[posx[i] = n][posy[i] = posy[i - 1] + 1] = i;
		else if (posy[i - 1] == n && posx[i - 1] != 1) a[posx[i] = posx[i - 1] - 1][posy[i] = 1] = i;
		else if (posy[i - 1] == n && posx[i - 1] == 1) a[posx[i] = posx[i - 1] + 1][posy[i] = posy[i - 1]] = i;
		else if (!a[posx[i - 1] - 1][posy[i - 1] + 1]) a[posx[i] = posx[i - 1] - 1][posy[i] = posy[i - 1] + 1] = i;
		else a[posx[i] = posx[i - 1] + 1][posy[i] = posy[i - 1]] = i;
	REP(i, 1, n)
		REP(j, 1, n)
			printf("%d%c", a[i][j], j ^ n ? ' ' : '\n');
	return 0;
}
