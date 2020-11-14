/*
	Problem:	5496-new-new.cpp
	Time:		2020-11-04 21:48
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

char s[maxn];
namespace PAM
{
	int len[maxn], fail[maxn], cnt[maxn], ch[maxn][26], lst, cur;
	void init()
	{
		cur = 1;
		len[1] = -1;
		fail[0] = 1;
	}
	int getfail(int x, int n)
	{
		while (s[n] ^ s[n - len[x] - 1]) x = fail[x];
		return x;		
	}
	void extend(int i)
	{
		int p = getfail(lst, i);
		int c = s[i];
		if (!ch[p][c])
		{
			++cur;
			len[cur] = len[p] + 2;
			fail[cur] = ch[getfail(fail[p], i)][c];
			cnt[cur] = cnt[fail[cur]] + 1;
			ch[p][c] = cur;
		}
		lst = ch[p][c];
	}
}
int n;

int main()
{
#ifdef CraZYali
	file("5496-new-new");
#endif
	PAM :: init();
	scanf("%s", s + 1);
	s[0] = 26;
	n = strlen(s + 1);
	int lstans = 0;
	REP(i, 1, n)
	{
		s[i] = (s[i] - 97 + lstans) % 26;
		PAM :: extend(i);
		printf("%d%c", lstans = PAM :: cnt[PAM :: lst], i == end_i ? '\n' : ' ' );
	}
	return 0;
}
