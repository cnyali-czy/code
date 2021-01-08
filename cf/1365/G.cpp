/*
	Problem:	G.cpp
	Time:		2021-01-03 20:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e3 + 10;

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

int n, id[maxn], res[20];

signed main()
{
#ifdef CraZYali
//	file("G");
#endif
	cin >> n;
	for (int i = 0, j = 1; j <= n; i++)
		if (__builtin_popcount(i) == 6) id[j++] = i;
	REP(i, 0, 12)
	{
		vector <int> q;
		REP(j, 1, n) if (id[j] >> i & 1) q.emplace_back(j);
		if (!q.size()) continue;
		cout << "? " << q.size();
		for (auto j : q) cout << ' ' << j;
		cout << endl;
		cin >> res[i];
	}
	cout << "!";
	REP(i, 1, n)
	{
		int ans = 0;
		REP(j, 0, 12)
			if (!(id[i] >> j & 1)) ans |= res[j];
		cout << ' ' << ans;
	}
	cout << endl;
	return 0;
}
