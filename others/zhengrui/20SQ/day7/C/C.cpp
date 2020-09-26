/*
	Problem:	C.cpp
	Time:		2020-09-19 22:21
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;

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

int b[6];

namespace bf
{
	const int maxb = 2000 + 10;

	void calc(int x, int y, int bit, int f[maxb][2])
	{
		REP(i, 0, max(x, y)) f[i][0] = f[i][1] = 0;
		REP(i, 0, x) REP(j, 0, y)
		{
			int delta = abs(i - j);
			f[delta][(i ^ j) >> bit & 1]++;
		}
	}
	void gets(int f[maxb][2], unsigned i64 s[maxb][2])
	{
		s[0][0] = f[0][0];s[0][1] = f[0][1];
		REP(i, 1, maxb - 1)
		{
			s[i][0] = s[i - 1][0] + f[i][0];
			s[i][1] = s[i - 1][1] + f[i][1];
		}
	}

	int fa[maxb][2], fb[maxb][2], fc[maxb][2];
	unsigned i64 sa[maxb][2], sb[maxb][2], sc[maxb][2];

	void work()
	{
		unsigned i64 ans = 0;
		REP(bit, 0, 11)
		{
			calc(b[0], b[3], bit, fa);gets(fa, sa);
			calc(b[1], b[4], bit, fb);gets(fb, sb);
			calc(b[2], b[5], bit, fc);gets(fc, sc);
			REP(Max, 0, 2000)
			{
				int bm = Max >> bit;
				unsigned i64 cur = 0, del = 0;
				REP(bit1, 0, 1) REP(bit2, 0, 1) REP(bit3, 0, 1) if (bit1 + bit2 + bit3 + bm & 1)
				{
					cur += sa[Max][bit1] * sb[Max][bit2] * sc[Max][bit3];
					if (Max) del += sa[Max - 1][bit1] * sb[Max - 1][bit2] * sc[Max - 1][bit3];
				}
				cur -= del;
				ans += (cur << bit);
			}
		}
		cout << ans << endl;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	REP(i, 0, 5) b[i] = read<int>();
	bf :: work();
	return 0;
}
