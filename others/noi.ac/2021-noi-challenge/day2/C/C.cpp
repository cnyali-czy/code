/*
	Problem:	C.cpp
	Time:		2021-06-20 10:09
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxc = 2000 + 10, maxs = maxc / 2 + 10;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int S, C;
bitset <maxc> b[maxs], all;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> S >> C;C /= 2;
	REP(i, 1, S) REP(j, 1, min(C - i, S / i))
		b[i * j][i + j] = 1;
	REP(i, 1, S) REP(j, 1, S / i)
		REP(k, 1, S - i * j) b[k + i * j] |= (b[k] << (i + j));
	long long ans = 0;
	REP(i, 1, C) all[i] = 1;
	REP(i, 1, S) ans += (b[i] & all).count();
	cout << ans << endl;
	return 0;
}
