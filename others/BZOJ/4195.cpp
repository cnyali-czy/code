/*
 * File Name:	4195.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.15 22:41
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2000000 + 10;

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

int m, fa[maxn];

int n, a[maxn];
pair <pair <int, int>, bool> QAQ[maxn];

int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}
#define hhakioi(x) (lower_bound(a + 1, a + 1 + n, x) - a)
int main()
{
#ifdef CraZYali
	file("4195");
#endif
	int T;cin >> T;
	while (T--)
	{
		m = read<int>();
		n = 0;
		REP(i, 1, m)
		{
			int x(read<int>()), y(read<int>()), opt(read<int>());
			a[++n] = x;a[++n] = y;
			QAQ[i] = make_pair(make_pair(x, y), (bool)opt);
		}
		sort(a + 1, a + 1 + n);
		n = unique(a + 1, a + 1 + n) - a - 1;
		REP(i, 1, n) fa[i] = i;
		REP(i, 1, m)
			if (QAQ[i].second) uni(hhakioi(QAQ[i].first.first), hhakioi(QAQ[i].first.second));
		bool flag(1);
		REP(i, 1, m)
			if (!QAQ[i].second && find(hhakioi(QAQ[i].first.first)) == find(hhakioi(QAQ[i].first.second)))
			{
				flag = 0;
				break;
			}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
