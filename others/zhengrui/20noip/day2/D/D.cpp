#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 5000 + 10;

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

inline bool chkmax(i64 &x, i64 y)
{
	if (x <= y)
	{
		x = y;
		return 1;
	}
	return 0;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], s[maxn];
i64 f[maxn][maxn];
i64 sum(int l, int r) {return s[r] - s[l - 1];}
int gd[maxn];

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 1, n) s[i] = s[i - 1] + (a[i] = read<int>());
	REP(i, 1, n) 
		REP(j, i, n)
		{
			gd[j] = 0;
			REP(k, 1, i - 1)
				if (chkmax(f[i][j], f[k][i - 1] + sum(k, i - 1) * sum(i, j))) gd[j] = k;
			printf("%d%c", gd[j], j == end_j ? '\n' : ' ');
		}
	i64 ans = 0;
	REP(i, 1, n) ans = max(ans, f[i][n]);
	cout << ans << endl;
	return 0;
}
