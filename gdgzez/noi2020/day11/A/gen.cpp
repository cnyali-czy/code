/*
	Problem:	gen.cpp
	Time:		2020-06-11 08:01
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

using namespace std;
#define int long long
const int maxn = 1e5 + 10, MOD = 998244353;

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
#include <ctime>

inline int Rand() {return 1ll * rand() * rand();}
inline int randint(int l, int r) {return Rand() % (r - l + 1) + l;}
signed main()
{
	srand(time(0));
	freopen("A.in", "w", stdout);
	int n = 20, m = 20;
	cout << n << ' ' << m << endl;
	int N = 10000;
	REP(i, 1, n) printf("%d%c", randint(1, N), i == n ? '\n' : ' ');
	while (m--)
	{
		int l = randint(1, n), r = randint(l, n), v = randint(1, N);
		printf("%d %d %d\n", l, r, 1);
	}
	return 0;
}
