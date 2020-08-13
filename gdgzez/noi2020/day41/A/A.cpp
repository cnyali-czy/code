/*
	Problem:	A.cpp
	Time:		2020-08-13 09:53
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
#include <iostream>
#include <cstdio>
#define y1 lbhyyds
using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10, maxq = 1e5 + 10;

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

int n, m, q;
int a[maxn][maxm], s[maxn][maxm], gd[maxn][maxn];

inline int id(int x, int y) {return (x - 1) * m + y;}
inline int sum(int x1, int y1, int x2, int y2)
{
	return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
}

const int maxN = maxn * maxm;
int N, fa[maxN];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}
bool ins(int x, int y) {return find(x) == find(y);}
int d[][2] = {{1, 0}, {0, 1}};
vector <pair <int, int> > add[maxn];

int x1[maxq], y1[maxq], x2[maxq], y2[maxq];
vector <int> ask[maxn];
bool ans[maxq];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, n) REP(j, 1, m)
	{
		char c = getchar();
		while (!isdigit(c)) c = getchar();
		a[i][j] = c - 48;
	}
	REP(i, 1, q)
	{
		x1[i] = read<int>();
		y1[i] = read<int>();
		x2[i] = read<int>();
		y2[i] = read<int>();
		ask[read<int>()].emplace_back(i);
	}
	REP(i, 1, n) REP(j, 1, m)
		s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
	REP(i, 1, n) REP(j, 1, m) if (!a[i][j])
	{
		int l = 1, r = min(i, j), res = 1;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (!sum(i - mid + 1, j - mid + 1, i, j))
			{
				res = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		gd[i][j] = res;
	}
	N = n * m;
	REP(i, 1, N) fa[i] = i;
	REP(x1, 1, n) REP(y1, 1, m) if (!a[x1][y1]) REP(qaq, 0, 1)
	{
		int x2 = x1 + d[qaq][0];
		int y2 = y1 + d[qaq][1];
		if (x2 > n || y2 > m || a[x2][y2]) continue;
		add[min(gd[x1][y1], gd[x2][y2])].emplace_back(id(x1, y1), id(x2, y2));
	}
	DEP(w, n, 1)
	{
		for (auto i : add[w]) uni(i.first, i.second);
		for (auto i : ask[w])
			if (x1[i] == x2[i] && y1[i] == y2[i])
				ans[i] = !sum(x1[i] - w + 1, y1[i] - w + 1, x1[i], y1[i]);
			else ans[i] = ins(id(x1[i], y1[i]), id(x2[i], y2[i]));
	}
	REP(i, 1, q)
		puts(ans[i] ? "Yes" : "No");
	return 0;
}
