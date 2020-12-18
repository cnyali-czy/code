/*
	Problem:	1368.cpp
	Time:		2020-12-04 18:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3e5 + 10;

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

namespace SAM
{
	const int maxn = ::maxn << 2;
	map <int, int> ch[maxn];
	int len[maxn], fail[maxn], lst = 1, cur = 1;
	void extend(int c)
	{
		int u = ++cur, v = lst;
		lst = u;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
		else
		{
			int New(++cur), Old(ch[v][c]);
			ch[New] = ch[Old];
			len[New] = len[v] + 1;
			fail[New] = fail[Old];
			fail[Old] = fail[u] = New;
			for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
		}
	}
}

int n, a[maxn];

int main()
{
#ifdef CraZYali
	file("1368");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) SAM :: extend(a[i]);
	REP(i, 1, n) SAM :: extend(a[i]);
	int p = 1;
	REP(i, 1, n)
	{
		auto E = SAM :: ch[p].begin();
		printf("%d%c", E -> first, i == end_i ? '\n' : ' ');
		p = E -> second;
	}
	return 0;
}
