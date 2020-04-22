/*
	Problem:	2408.cpp
	Time:		2020-04-05 20:25
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
const int maxn = 2e5 + 10;

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

int n;
char s[maxn];

const int siz = 26;
struct node
{
	int ch[siz], len, fail;
	inline int &operator [] (const int &x) {return ch[x];}
}p[maxn];
int lst, cur;
struct __init__
{
	__init__()
	{
		lst = cur = 1;
		REP(i, 0, siz - 1) p[1][i] = 0;
		p[1].fail = 0;
		p[1].len = 0;
	}
}__INIT__;
#define fail(x) p[x].fail
#define len(x) p[x].len
void extend(char c)
{
	int u = ++cur, v = lst;
	len(u) = len(v) + 1;
	for (; v && !p[v][c]; v = fail(v)) p[v][c] = u;
	if (!v) fail(u) = 1;
	else if (len(p[v][c]) == len(v) + 1) fail(u) = p[v][c];
	else
	{
		int Old(p[v][c]), New(++cur);
		copy(p[Old].ch, p[Old].ch + siz, p[New].ch);
		len(New) = len(v) + 1;
		fail(New) = fail(Old);
		fail(Old) = fail(u) = New;
		for (; v && p[v][c] == Old; v = fail(v)) p[v][c] = New;
	}
	lst = u;
}

int main()
{
#ifdef CraZYali
	file("2408");
#endif
	n = read<int>();
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	REP(i, 1, n)
	{
		extend(c - 'a');
		if (i < n) c = getchar();
	}
	long long ans = 0;
	REP(i, 1, cur) ans += len(i) - len(fail(i));
	cout << ans << endl;
	return 0;
}
