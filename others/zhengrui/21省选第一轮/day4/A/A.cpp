#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 5e5 + 10, inf = 1e15;

int n, k, a[maxn], b[maxn];

int f[maxn][3];
//0 : a = b
//1 : a > b
//2 : a < b
void chkmax(int &x, int y) {x = max(x, y);}
namespace bf
{
	const int maxn = 505;
	int f[maxn][maxn];
	int main()
	{
		REP(i, 1, n) REP(j, 1, n) f[i][j] = -inf;
		f[1][1] = a[1] + b[1];
		REP(i, 1, n) REP(j, 1, n)
		{
			REP(l, j + 1, n) if (abs(l - i) <= k) chkmax(f[i][l], f[i][j] + b[l]);
			REP(l, i + 1, n) if (abs(l - j) <= k) chkmax(f[l][j], f[i][j] + a[l]);
		}
		cout << f[n][n] << endl;
		return 0;
	}
}
signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n) scanf("%lld", a + i);
	REP(i, 1, n) scanf("%lld", b + i);
	if (n <= 500 && k <= 500) return bf :: main();
	REP(i, 1, n) f[i][0] = f[i][1] = f[i][2] = -inf;
	f[1][0] = a[1] + b[1];
	REP(i, 1, n)
	{
		int ra = 0, rb = 0;
		chkmax(f[i][0], f[i][1] + b[i]);
		chkmax(f[i][0], f[i][2] + a[i]);
		REP(j, i + 1, min(n, i + k))
		{
			ra += a[j];
			rb += b[j];
		//	chkmax(f[j][0], f[i][1] + rb + max(b[i], 0ll) + ra);?
			chkmax(f[j][2], f[i][1] + rb + max(b[i], 0ll) + ra - a[j]);//b[j]);
		//	chkmax(f[j][0], f[i][2] + ra + max(a[i], 0ll) + rb);?
			chkmax(f[j][1], f[i][2] + ra + max(a[i], 0ll) + rb - b[j]);//a[j]);
			if (j > i)
			{
				chkmax(f[j][1], f[i][0] + ra + rb - b[j]);//a[j]);
				chkmax(f[j][2], f[i][0] + rb + ra - a[j]);//b[j]);
			}
			ra -= min(a[j], 0ll);
			rb -= min(b[j], 0ll);
		}
	}
//	REP(i, 1, n) printf("%2lld %2lld %2lld\n", f[i][0], f[i][1], f[i][2]);
	cout << f[n][0] << endl;
	return 0;
}
