/*
	Problem:	F.cpp
	Time:		2021-03-23 19:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <vector>
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

const int w = 20;
int n, q, a[maxn];

int ans[maxn];
vector <pair <int, int > > qry[maxn];

int p[w], t[w];
void ins(int x, int y)
{
	DEP(i, w - 1, 0) if (x >> i & 1)
		if (!p[i]) {p[i] = x;t[i] = y;return;}
		else
		{
			if (y > t[i])
			{
				swap(x, p[i]);
				swap(y, t[i]);
			}
			x ^= p[i];
		}
}
int query(int T)
{
	int res = 0;
	DEP(i, w - 1, 0) if (t[i] >= T) res = max(res, res ^ p[i]);
	return res;
}

int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	q = read<int>();
	REP(i, 1, q)
	{
		int l = read<int>(), r = read<int>();
		qry[r].emplace_back(l, i);
	}

	REP(i, 1, n)
	{
		ins(a[i], i);
		for (auto Q : qry[i])
			ans[Q.second] = query(Q.first);
	}

	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
