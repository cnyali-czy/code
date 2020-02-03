/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.28 13:53
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 
#include <cmath>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>

using namespace std;

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

int n, m, p, ans;
map <int, int> cnt;
set <int> S;
int stack[2333], top;
int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m >> p;
	REP(i, 1, n)
	{
		int x = -read<int>();
		if (!cnt[x]) S.emplace(x);
		cnt[x]++;
	}
	int ans(0);
	while (m--)
	{
		int opt = read<int>();
		if (opt == 1)
		{
			int x = -(read<int>() ^ (p * ans));
			if (!cnt[x]) S.emplace(x);
			cnt[x]++;
		}
		else if (opt == 2)
		{
			int x = -(read<int>() ^ (p * ans));
			cnt[x]--;
			if (!cnt[x]) S.erase(x);
		}
		else
		{
			int l(read<int>() ^ (p * ans)), r(read<int>() ^ (p * ans));
			int lim = 35;
			auto it = S.lower_bound(-r);
			top = 0;
			ans = 0;
			while (it != S.end() && *it <= -l && lim)
			{
				lim--;
				stack[++top] = -*it;
				if (cnt[-stack[top]] > 1)
				{
					ans = stack[top];
					break;
				}
				it++;
			}
			REP(i, 1, top)
				REP(j, i + 1, top) chkmax(ans, stack[i] & stack[j]);
			printf("%d\n", ans);
		}
	}
	return 0;
}
