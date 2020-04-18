/*
	Problem:	F.cpp
	Time:		2020-04-09 00:06
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <set>
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

int n, prime[maxn], p_cnt;
bool notp[maxn];
vector <int> v[maxn];
void init()
{
	REP(i, 2, n)
	{
		if (!notp[i]) prime[++p_cnt] = i;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > n) break;
			notp[tmp] = 1;
			v[i].emplace_back(tmp);
			if (i % prime[j] == 0) break;
		}
	}
}

int ans[maxn];
int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();
	init();
	REP(i, 1, p_cnt + 1) ans[i] = 1;
	int cur = p_cnt + 1;
	REP(i, 2, n)
	{
		for (auto j : v[i])
		{
			ans[++cur] = i;
			if (cur > n) break;
		}
		if (cur > n) break;
	}
	REP(i, 2, n) printf("%d%c", ans[i], i == end_i ? '\n' : ' ');
	return 0;
}
