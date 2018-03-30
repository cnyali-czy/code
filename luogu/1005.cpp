#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 100, maxm = 100;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
template <typename T> void write(T num)
{
	if (!num) return;
	else if (num < 0)
	{
		putchar('-');
		write(-num);
	}
	else
	{
		write(num / 10);
		putchar(num % 10 + '0');
	}
}

int m, n, k;
typedef __int128 BigInt;
BigInt a[maxn][maxm], re[maxm][maxm];

BigInt dp(int l, int r, int LINE)
{
	if (l > r) return 0;
	if (re[l][r]) return re[l][r];
	else return re[l][r] = max(	dp(l + 1, r, LINE) + a[LINE][l] * ((BigInt)1 << (BigInt)(m - (r - l))),
								dp(l, r - 1, LINE) + a[LINE][r] * ((BigInt)1 << (BigInt)(m - (r - l))));
}

int main()
{
#ifdef CraZYali
	freopen("1005.in", "r", stdin);
	freopen("1005.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, n)
		REP(j, 1, m)
			a[i][j] = read<BigInt>();
	BigInt ans = 0;
	REP(i, 1, n)
	{
		memset(re, 0, sizeof(re));
		ans += dp(1, m, i);
	}
	if (ans) write(ans);
	else cout << 0;
	return 0;
}
