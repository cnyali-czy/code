/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.07 21:00
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <set>
#define int long long
using namespace std;
const int maxn = 3e5 + 10, MOD = 998244353;

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

int n, m;
long long ans(1);
set <int> s[maxn];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m;
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		s[min(x, y)].insert(max(x, y));
	}
	REP(x, 1, n)
	{
		(ans *= (n - (int)s[x].size())) %= MOD;
		int y(*s[x].begin());
		s[x].erase(y);
		if (s[x].size() > s[y].size()) s[y].swap(s[x]);
		for (auto it = s[x].begin(); it != s[x].end(); it++) s[y].insert(*it);
		set<int>().swap(s[x]);
	}
	cout << (ans + MOD) % MOD << endl;
	return 0;
}
