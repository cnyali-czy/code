/*
	Problem:	5496-new.cpp
	Time:		2020-02-25 21:04
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10;

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

char s[maxn];

namespace PAM
{
	int fail[maxn], ch[maxn][26], cur, len[maxn], lst, num[maxn];
	void init()
	{
		fail[0] = 1;
		len[1] = -1;
		cur = 1;
	}
	int get_fail(int u, int n)
	{
		while (s[n] != s[n - len[u] - 1]) u = fail[u];
		return u;
	}
	void insert(int i)
	{
		int p = get_fail(lst, i);
		if (!ch[p][s[i]])
		{
			++cur;
			len[cur] = len[p] + 2;
			fail[cur] = ch[get_fail(fail[p], i)][s[i]];
			num[cur] = num[fail[cur]] + 1;
			ch[p][s[i]] = cur;
		}
		lst = ch[p][s[i]];
	}
}
int n;

int main()
{
#ifdef CraZYali
	file("5496-new");
#endif
	s[0] = 26;
	scanf("%s", s + 1);
	PAM::init();
	int lastans = 0;
	n = strlen(s + 1);
	REP(i, 1, n)
	{
		s[i] = (s[i] - 97 + lastans) % 26;
		PAM::insert(i);
		cout << (lastans = PAM::num[PAM::lst]) << ' ';
	}
	return 0;
}
