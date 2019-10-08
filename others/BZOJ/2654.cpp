/*
 * File Name:	2654.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.08 16:10
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
const int maxn = 50000 + 10, maxm = 1e5 + 10;
const double eps = 1e-8;

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

int n, m, k;
double mid;

struct edge
{
	int col, x, y, z;
	inline double get_order() {return col ? z : z + mid;}
}E[maxm];
inline bool cmp(edge A, edge B)
{
	return A.get_order() < B.get_order();
}

int fa[maxn];
inline void clear()
{
	REP(i, 1, n) fa[i] = i;
}
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}

int main()
{
#ifdef CraZYali
	freopen("/Users/sun/Downloads/2654/3.in", "r", stdin);
	freopen("2654.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	REP(i, 1, m)
	{
		register int x(read<int>() + 1), y(read<int>() + 1), z(read<int>()), col(read<int>());
		E[i] = edge{col, x, y, z};
	}
	register double l(-100), r(100);
	register int ans(1e9);
	while (r - l > eps)
	{
		mid = (l + r) / 2;
		sort(E + 1, E + 1 + m, cmp);
		clear();
		register int res(0), cnt(0);
		REP(i, 1, m)
		{
			register int x(E[i].x), y(E[i].y);
			if (find(x) == find(y)) continue;
			else
			{
				cnt += (!E[i].col);
				res += E[i].z;
				uni(x, y);
			}
		}
		if (cnt == k)
		{
			cout << res << endl;
			return 0;
		}
		else if (cnt < k)
			r = mid;
		else
		{
			chkmin(ans, res);
			l = mid;
		}
	}
	cout << ans << endl;
	return 0;
}
