/*
	Problem:	D.cpp
	Time:		2021-02-18 09:29
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <unordered_map>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e9 + 10;

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

int n;
unordered_map <int, i64> mem;
i64 f(const int n)
{
	if (n == 1) return 1;
	if (mem.find(n) != mem.end()) return mem[n];
	i64 ans = 0;
	for (int i = 2, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		ans += (j - i + 1) * f(n / i);
	}
	return mem[n] = ans;
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	cout << f(n) << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
