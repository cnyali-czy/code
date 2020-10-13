/*
	Problem:	D.cpp
	Time:		2020-10-11 20:27
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

int main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		scanf("%d\n%s", &n, s + 1);
		static int stk[maxn], top;
		top = 0;
		for (int i = 1, j; i <= n; i = j + 1)
		{
			j = i;
			while (j < n && s[j + 1] == s[i]) j++;
			stk[++top] = j - i + 1;
		}
		int ans = 0;
		for (int i = 1, j = 1; i <= top; i++)
		{
			j = max(j, i);
			while (j <= top && stk[j] == 1) j++;
			if (j <= top) stk[j]--;
			else i++;
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
