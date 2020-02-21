/*
	Problem:	A.cpp
	Time:		2020-02-21 13:53
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
#define i64 long long
using namespace std;
const int maxm = 400 + 5, MOD = 1e9 + 7;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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

int m, k, s;
int l[maxm], r[maxm];

namespace two
{
	bitset <200000005> In;
	void work()
	{
		REP(i, 1, m) REP(j, l[i], r[i]) In[j] = 1;
		int ans = 0;
		REP(i, 1, m) REP(j, l[i], min((s - 1) / 2, r[i])) if (In[s - j]) ans++;
		cout << ans << '\n';
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	m = read<int>();k = read<int>();s = read<int>();
	REP(i, 1, m) l[i] = read<int>(), r[i] = read<int>();
	if (k == 2) two::work();
	return 0;
}
