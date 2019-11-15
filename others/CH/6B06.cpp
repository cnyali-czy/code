/*
 * File Name:	6B06.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.15 09:23
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20;

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

int n, m, tot;
int fa[maxn], siz[maxn];
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}

struct edge
{
	int x, y, z;
	inline bool operator < (const edge &B) const {return z < B.z;}
}E[maxn * maxn];

int main()
{
#ifdef CraZYali
	file("6B06");
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, n)
	{
		int a = read<int>();
		if (a)
		{
			siz[i] = 1;
			tot++;
		}
		fa[i] = i;
	}
	if (!tot)
	{
		puts("0");
		return 0;
	}
	REP(i, 1, m)
	{
		int x(read<int>() + 1), y(read<int>() + 1), z(read<int>());
		E[i] = edge{x, y, z};
	}
	sort(E + 1, E + 1 + m);
	int ans(0);
	bool flag(0);
	REP(i, 1, m)
	{
		int x(find(E[i].x)), y(find(E[i].y));
		if (x ^ y)
		{
			siz[x] += siz[y];
			fa[y] = x;
			ans += E[i].z;
			if (siz[x] == tot)
			{
				flag = 1;
				break;
			}
		}
	}
	if (flag) cout << ans << endl;
	else puts("Impossible");
	return 0;
}
