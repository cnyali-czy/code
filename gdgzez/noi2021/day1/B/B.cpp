/*
	Problem:	B.cpp
	Time:		2021-02-25 17:33
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxq = 2e5 + 10;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, q;
pair <int, int> qry[maxq];
string ans[maxq];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m >> q;
	REP(i, 1, q) qry[i] = make_pair(read<int>(), i);
	sort(qry + 1, qry + 1 + q);
	string s = "a";
	int j = 1;
	REP(i, 1, q)
	{
		while (j != qry[i].first)
		{
			j++;
			while (s.size() < n) s += s;
			s.resize(n);
			while (s.size() > 1 && s.back() == 'a' + m - 1) s.pop_back();
			s[s.size() - 1]++;
		}
		ans[qry[i].second] = s;
	}
	REP(i, 1, q) cout << ans[i] << '\n';
	return 0;
}
