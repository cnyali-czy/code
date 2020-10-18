#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1000 + 10;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;
int v[maxn][maxn];

const int delta = 1000;
int ro[maxn], co[maxn], dj[maxn << 1];

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) REP(j, 1, m) v[i][j] = read<int>();
	DEP(i, n, 2) DEP(j, m, 2) v[i][j] -= v[i - 1][j - 1];
	REP(i, 2, m) co[i] = v[2][i];
	REP(i, 3, n)
	{
		ro[i] = v[i][2] - co[2];
		REP(j, 3, m) if (ro[i] + co[j] != v[i][j])
		{
			puts("-1");
			return 0;
		}
	}
	REP(i, 2, n) ro[i] += ro[i - 1];
	REP(i, 2, m) co[i] += co[i - 1];
	dj[delta] = v[1][1];
	REP(i, 2, n) dj[delta + i - 1] = v[i][1] - ro[i];
	REP(i, 2, m) dj[delta + 1 - i] = v[1][i] - co[i];
	cout << n + m + n + m - 1 << endl;
	REP(i, 1, n) printf("1 %lld %lld\n", i, -ro[i]);
	REP(i, 1, m) printf("2 %lld %lld\n", i, -co[i]);
	REP(i, 1 - n, m - 1) printf("3 %lld %lld\n", i, -dj[delta - i]);


	return 0;
}
