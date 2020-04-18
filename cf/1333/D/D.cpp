/*
	Problem:	D.cpp
	Time:		2020-04-08 23:18
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3000 + 10;

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
int n, k;
char s[maxn];
vector <int> v[maxn];
int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();k = read<int>();
	scanf("%s", s + 1);
	int Min(0), Max(0);
	bool flag = 1;
	int cnt = 0;
	while (flag)
	{
		flag = 0;
		cnt++;
		REP(i, 2, n)
			if (s[i - 1] == 'R' && s[i] == 'L')
			{
				swap(s[i-1], s[i]);
				v[cnt].emplace_back(i-1);
				i++;
				Max++;
				flag = 1;
			}
		if (!flag) break;
		Min++;
	}
	if (!(Min <= k && k <= Max)) puts("-1");
	else
	{
		int less = k - Min, tot = 0;
		REP(i, 1, Min)
		{
			while (v[i].size() > 1 && less)
			{
				less--;
				printf("1 %d\n", v[i].back());
				v[i].pop_back();
			}
			printf("%d", (int)v[i].size());
			for (auto j : v[i]) printf(" %d", j);
			puts("");
		}
	}
	return 0;
}
