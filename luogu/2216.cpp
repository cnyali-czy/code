#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxa = 1000 + 10, maxb = 1000 + 10, maxL = 10;

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
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int a, b, n, A[maxa][maxb], mx[maxa][maxb][maxL], mi[maxa][maxb][maxL];

int main()
{
#ifdef CraZYali
	freopen("2216.in", "r", stdin);
	freopen("2216.out", "w", stdout);
#endif
	cin >> a >> b >> n;
	REP(i, 1, a)
		REP(j, 1, b) A[i][j] = mx[i][j][0] = mi[i][j][0] = read<int>();

	REP(k, 1, maxL)
		REP(i, 1, a)
		REP(j, 1, b)
		{
			int xe = i + (1 << k) - 1, ye = j + (1 << k) - 1;
			if (xe > a || ye > b) continue;
			mx[i][j][k] = max(mx[i][j][k-1], max(mx[i][j + (1 << k - 1)][k-1], max(mx[i + (1 << k - 1)][j][k-1], mx[i + (1 << k - 1)][j + (1 << k - 1)][k-1])));
			mi[i][j][k] = min(mi[i][j][k-1], min(mi[i][j + (1 << k - 1)][k-1], min(mi[i + (1 << k - 1)][j][k-1], mi[i + (1 << k - 1)][j + (1 << k - 1)][k-1])));
		}

	int Max, Min, ans = 1e9, k = log2(n);
	REP(i, 1, a - n + 1)
		REP(j, 1, b - n + 1)
		{
			Max = max(max(mx[i][j][k], mx[i][j + n - (1 << k)][k]), max(mx[i + n - (1 << k)][j][k] , mx[i + n - (1 << k)][j + n - (1 << k)][k]));
			Min = min(min(mi[i][j][k], mi[i][j + n - (1 << k)][k]), min(mi[i + n - (1 << k)][j][k] , mi[i + n - (1 << k)][j + n - (1 << k)][k]));
			chkmin(ans, Max - Min);
		}
	cout << ans << endl;
	return 0;
}
