/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.12 21:11
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxm = 1e5 + 10;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

struct brush
{
	int c, l, r;
	inline bool operator < (const brush &B) const {return r < B.r;}
}b[maxm];
int n, m, c[maxm], l[maxm], r[maxm];
long long x, y, ans, dp[maxm];

const long long inf = 1e18;
long long M[4][(int)1e4], MM[2][4][(int)1e4];

int main()
{
#ifdef CraZYali
	freopen("A.in","r",stdin);
	freopen("bbf.out","w",stdout);
#endif
	cin >> n >> m >> x >> y;
	REP(i, 1, m)
	{
		b[i].c = read<int>();
		b[i].l = read<int>();
		b[i].r = read<int>();
	}
	REP(i, 0, n) REP(j,0,3)MM[0][j][i] = MM[1][j][i] = M[0][i] = M[1][i] = M[2][i] = M[3][i] = -inf;
	sort(b + 1, b + 1 + m);
	REP(i, 1, m)
	{
		int c(b[i].c), l(b[i].l), r(b[i].r);
		dp[i] = x * (r - l + 1);
		if (i > 1 && l > 1)
			REP(I, 1, l - 1) chkmax(dp[i], M[0][I] + x * (r - l + 1));
		REP(j, 1, 3)
			if (j == c)
				chkmax(dp[i], x * r + MM[0][j][l]);
			else
				chkmax(dp[i], x * r + (x + y) * (l - 1) + MM[1][j][l]);
		chkmax(M[0][r], dp[i]);
		REP(I, l + 1, r)
		{
			chkmax(MM[0][c][I], dp[i] - r * x);
			REP(j, 1, 3) if (c ^ j) chkmax(MM[1][j][I], dp[i] - x * r - (x + y) * r);
		}
	}
	REP(i, 1, m) printf("%lld%c", dp[i], i == m ? '\n' : ' ');
	long long ans(dp[1]);
	REP(i, 2, m) chkmax(ans, dp[i]);
	cout << ans << endl;
	return 0;
}
