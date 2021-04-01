/*
	Problem:	6622.cpp
	Time:		2021-03-31 19:22
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
#define i64 int

using namespace std;
const int maxm = 23;
const int inf = (1ll << 31) - 1;

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

int n, m, cnt[30][30], k;
int f[1 << 23];

unsigned sum[2][1 << 12][23];
inline unsigned mp(unsigned x, unsigned y) {return x << 16 | y;}
inline unsigned fi(unsigned x) {return x >> 16;}
inline unsigned se(unsigned x) {return x & 65535;}

inline int lg(int x) {return 31 - __builtin_clz(x);}
int si_[30], s_i[30];

int main()
{
#ifdef CraZYali
	file("6622");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	int lst = 0;
	REP(i, 1, n)
	{
		int x = read<int>();
		if (lst != x && lst) cnt[lst][x]++;
		lst = x;
	}
	REP(i, 1, m) REP(j, 1, m)
	{
		si_[i] += cnt[i][j];
		s_i[j] += cnt[i][j];
	}
	REP(i, 0, (1 << m) - 1) f[i] = inf;
	f[0] = 0;
	const int MID = m + 1 >> 1, W = (1 << MID) - 1;
	//f[S] 编号集合 S 的已经放置好了
	REP(S, 1, (1 << MID) - 1)
	{
		int lowbit = lg(S & -S), oS = S & (S - 1);
		REP(i, 1, m)
		{
			sum[0][S][i - 1] = sum[0][oS][i - 1] + mp(cnt[lowbit + 1 ][i], cnt[i][lowbit + 1 ]);
			sum[1][S][i - 1] = sum[1][oS][i - 1] + mp(cnt[lowbit + 1 + MID][i], cnt[i][lowbit + 1 + MID]);
		}
	}
	REP(S, 0, (1 << m) - 1) if (f[S] < inf)
	{
		unsigned newpos = __builtin_popcount(S) + 1;
		REP(i, 1, m) if (!(S >> (i - 1) & 1)) // 新安排一个 i
		{
			unsigned fk = sum[0][S & W][i - 1] + sum[1][S >> MID][i - 1];
			int s1 = fi(fk), s2 = se(fk);
			int s3 = si_[i] - s2, s4 = s_i[i] - s1;
			/*
			   REP(j, 1, m) if (j ^ i)
			   {
			   if (S >> (j - 1) & 1)
			   {
			// ... j ... i ...
			//					s1 += cnt[j][i];
			//					s2 += cnt[i][j];
			//					res += newpos * cnt[j][i];		// j -> i
			//					res += k * newpos * cnt[i][j];	// i -> j
			}
			else
			{
			// ... i ... j ...
			//					s3 += cnt[i][j];
			//					s4 += cnt[j][i];
			//					res -= newpos * cnt[i][j];		// i -> j
			//					res += k * newpos * cnt[j][i];	// j -> i
			}
			}*/
//			unsigned
			i64 res = f[S];
			res += newpos * s1;
			res += k * newpos * s2;
			res += k * newpos * s4;
			res -= newpos * s3;

			f[S | (1 << i - 1)] = min(f[S | (1 << i - 1)], res);
		}
	}
	cout << f[(1 << m) - 1] << endl;
	return 0;
}
