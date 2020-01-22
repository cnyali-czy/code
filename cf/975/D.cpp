/*
 * File Name:	D.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.22 21:46
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <map>
#include <vector>

#define int long long
using namespace std;
const int maxn = 200000 + 10;
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

int n, a, b;
map <int, int> cnt;
map <int, map <pair <int, int>, int> > ban;

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	cin >> n >> a >> b;
	REP(i, 1, n)
	{
		int x(read<int>()), vx(read<int>()), vy(read<int>());
		int han = vy - a * vx;
		cnt[han]++;
		ban[han][make_pair(vx, vy)]++;
	}
	int ans = 0;
	for (auto i : cnt)
	{
		ans += i.second * (i.second - 1);
		for (auto j : ban[i.first]) ans -= j.second * (j.second - 1);
	}
	cout << ans << endl;
	return 0;
}
