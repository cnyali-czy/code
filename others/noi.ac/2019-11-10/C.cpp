/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.10 09:59
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 100;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int siz, n;
char s[maxn];

string ans;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	bool first(1);
	while (scanf("%d %s\n", &siz, s + 1) != EOF && siz)
	{
		if (first) first = 0;
		else putchar(10);
		ans = "";
		n = strlen(s + 1);
		REP(i, 1, n) s[i] -= '0';
		//先输出第一行
		REP(i, 1, n)
		{
			//每个数字占地是2 [ ] + siz + [ ]
			ans += ' ';
			if (s[i] ^ 1 && s[i] ^ 4)
				REP(i, 1, siz) ans += '-';
			else
				REP(i, 1, siz) ans += ' ';
			ans += "  ";
		}
		ans += '\n';
		//输出中上部分
		REP(tms, 1, siz)
		{
			REP(i, 1, n)
			{
				if (s[i] == 0 || s[i] == 4 || s[i] == 5 || s[i] == 6 || s[i] == 8 || s[i] == 9)
					ans += '|';
				else
					ans += ' ';
				REP(i, 1, siz) ans += ' ';
				if (s[i] == 0 || s[i] == 1 || s[i] == 2 || s[i] == 3 || s[i] == 4 || s[i] == 7 || s[i] == 8 || s[i] == 9)
					ans += '|';
				else
					ans += ' ';
				ans += ' ';
			}
			ans += '\n';
		}
		//输出中间部分
		REP(i, 1, n)
		{
			ans += ' ';
			if (s[i] == 2 || s[i] == 3 || s[i] == 4 || s[i] == 5 || s[i] == 6 || s[i] == 8 || s[i] == 9)
				REP(i, 1, siz) ans += '-';
			else
				REP(i, 1, siz) ans += ' ';
			ans += "  ";
		}
		ans += '\n';

		//输出中下部分
		REP(tms, 1, siz)
		{
			REP(i, 1, n)
			{
				if (s[i] == 0 || s[i] == 2 || s[i] == 6 || s[i] == 8)
					ans += '|';
				else
					ans += ' ';
				REP(i, 1, siz) ans += ' ';
				if (s[i] == 0 || s[i] == 1 || s[i] == 3 || s[i] == 4 || s[i] == 5 || s[i] == 6 || s[i] == 7 || s[i] == 8 || s[i] == 9)
					ans += '|';
				else
					ans += ' ';
				ans += ' ';
			}
			ans += '\n';
		}

		//输出最后一行
		REP(i, 1, n)
		{
			ans += ' ';
			if (s[i] == 0 || s[i] == 2 || s[i] == 3 || s[i] == 5 || s[i] == 6 || s[i] == 8 || s[i] == 9)
				REP(i, 1, siz) ans += '-';
			else
				REP(i, 1, siz) ans += ' ';
			ans += "  ";
		}
		ans += '\n';

		//输出
		vector <bool> need(ans.size(), 0);
		bool flag(0);
		DREP(i, ans.size(), 0)
		{
			if (ans[i] == '\n')
			{
				flag = 1;
				need[i] = 1;
			}
			else if (ans[i] == ' ' && !flag)
				need[i] = 1;
			else if (ans[i] == '|' || ans[i] == '-')
			{
				flag = 0;
				need[i] = 1;
			}
		}
		REP(i, 0, ans.size() - 1)
			if (need[i]) cout << ans[i];
	}
	return 0;
}
