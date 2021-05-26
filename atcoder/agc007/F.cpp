/*
	Problem:	2173.cpp
	Time:		2021-05-08 10:02
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

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

int n, ans;
string s, t;

int main()
{
#ifdef CraZYali
	file("2173");
#endif
	cin >> n >> s >> t;
	if (s == t) return 0 * puts("0");
	int u = n - 1, d = n - 1;
	queue <int> que;
	while (d >= 0)
	{
		while (d >  0 && t[d - 1] == t[d]) d--;
		while (u >= 0 && (s[u] != t[d] || u > d)) u--;
		if (u < 0) return 0 * puts("-1");
		while (que.size() && que.front() >= d + que.size()) que.pop();
		if (u ^ d) que.emplace(u);
		ans = max(ans, (int)que.size() + 1);
		d--;
	}
	cout << ans << endl;

	return 0;
}
