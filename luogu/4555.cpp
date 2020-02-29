/*
	Problem:	4555.cpp
	Time:		2020-02-29 19:54
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int n, mem1[maxn], mem2[maxn];
char s[maxn];

struct PAM
{
	int ch[maxn][26], len[maxn], lst, cur, fail[maxn];
	PAM()
	{
		len[1] = -1;len[0] = 0;
		fail[0] = 1;fail[1] = 1;
		lst = 0;
		cur = 1;
	}
	inline int getfail(int x, int n)
	{
		while (s[n] != s[n - len[x] - 1]) x = fail[x];
		return x;
	}
	inline void extend(int n)
	{
		int p = getfail(lst, n);
		if (!ch[p][s[n]])
		{
			++cur;
			len[cur] = len[p] + 2;
			fail[cur] = ch[getfail(fail[p], n)][s[n]];
			ch[p][s[n]] = cur;
		}
		lst = ch[p][s[n]];
	}
}A, B;

int main()
{
#ifdef CraZYali
	file("4555");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	s[0] = '#';
	REP(i, 1, n) s[i] -= 'a';
	REP(i, 1, n)
	{
		A.extend(i);
		mem1[i] = A.len[A.lst];
	}
	reverse(s + 1, s + 1 + n);
	REP(i, 1, n)
	{
		B.extend(i);
		mem2[n - i + 1] = B.len[B.lst];
	}
	int ans = 0;
	REP(i, 2, n) chkmax(ans, mem1[i-1] + mem2[i]);
	cout << ans << endl;
	return 0;
}
