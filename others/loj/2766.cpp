/*
	Problem:	2766.cpp
	Time:		2020-03-26 20:10
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 5e4 + 10;

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

inline bool query(int l, int r)
{
	printf("? %d %d\n", l, r);fflush(stdout);
	char ssr[10];
	scanf("%s", ssr);
	return ssr[0] == 'Y';
}

int stack[maxn], top;
char s[maxn];

int main()
{
	int n = read<int>();
	REP(i, 1, n)
	{
		if (!top) stack[++top] = i;
		else if (query(stack[top], i))
		{
			s[stack[top--]] = '(';
			s[i] = ')';
		}
		else stack[++top] = i;
	}
	printf("! %s\n", s + 1);
	fflush(stdout);
	return 0;
}
