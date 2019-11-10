/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.10 10:41
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;

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

int n, m;
int A[15][15];

__int128 zy[15][15], tmp[15][15], base[15][15], ans[15][15];

bool flag;
inline bool check(__int128 a[15][15])
{
	__int128 res(0);
	REP(i, 1, m)
	{
		res += a[i][m+1];
		if (res >= n) return flag = 1;
	}
	return 0;
}

inline void power_pow(int b)
{
	REP(i, 1, m + 1)
		REP(j, 1, m + 1) base[i][j] = zy[i][j];
	bool first(1);
	while (b)
	{
		if (check(base)) return;
		if (b & 1)
			if (first)
			{
				first = 0;
				REP(i, 1, m + 1)
					REP(j, 1, m + 1) ans[i][j] = base[i][j];
				if (check(ans)) return;
			}
			else
			{
				REP(i, 1, m + 1)
					REP(j, 1, m + 1) tmp[i][j] = 0;
				REP(i, 1, m + 1)
					REP(k, 1, m + 1) if (ans[i][k])
					REP(j, 1, m + 1)
					tmp[i][j] += ans[i][k] * base[k][j];
				REP(i, 1, m + 1)
					REP(j, 1, m + 1)
					ans[i][j] = tmp[i][j];
				if (check(ans)) return;
			}
		REP(i, 1, m + 1)
			REP(j, 1, m + 1) tmp[i][j] = 0;
		REP(i, 1, m + 1)
			REP(k, 1, m + 1) if (base[i][k])
			REP(j, 1, m + 1)
			tmp[i][j] += base[i][k] * base[k][j];
		REP(i, 1, m + 1)
			REP(j, 1, m + 1)
			base[i][j] = tmp[i][j];
		b >>= 1;
	}
	check(ans);
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m;
	if (!n)
	{
		puts("0");
		return 0;
	}
	REP(i, 1, m)
		REP(j, 1, m)
		{
			int tmp;
			scanf("%1lld", &tmp);
			zy[i][j] = tmp;
		}
	REP(i, 1, m + 1) zy[i][m + 1] = 1;
	int l(1), r(1e18);
	while (l <= r)
	{
		int mid = l + r >> 1;
		flag = 0;
		power_pow(mid);
		if (flag) r = mid - 1;
		else l = mid + 1;
	}
	cout << r + 1 << endl;
	return 0;
}
