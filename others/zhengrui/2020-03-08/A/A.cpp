/*
	Problem:	A.cpp
	Time:		2020-03-08 08:49
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
const int maxn = 30000 + 10, maxm = 90000 + 10;

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

int n, m, u[maxn], v[maxn], ans[maxn];
bitset <maxn> s[maxn];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n - 1) u[i] = read<int>(), v[i] = read<int>();
	REP(i, 1, n) s[i].set(i), ans[i] = 1;
	while (m--)
	{
		/*
		puts("--------------");
		REP(i, 1, n)
		{
			for (int x = s[i]._Find_first(); x != maxn; x = s[i]._Find_next(x)) cout << x << ' ' ;cout << endl;
		}
		puts("--------------");
		*/
		int opt = read<int>();
		if (opt == 1) cout << ans[read<int>()] << '\n';
		else
		{
			int p = read<int>();
			bitset <maxn> Newu = s[u[p]] & (s[u[p]] ^ s[v[p]]), Newv = s[v[p]] & (s[v[p]] ^ s[u[p]]);
			for (int x = Newu._Find_first(); x != maxn; x = Newu._Find_next(x)) ans[x]++;
			for (int x = Newv._Find_first(); x != maxn; x = Newv._Find_next(x)) ans[x]++;
			s[u[p]] = s[v[p]] = (s[u[p]] | s[v[p]]);
		}
	}
	return 0;
}
