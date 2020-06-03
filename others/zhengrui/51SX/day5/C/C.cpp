/*
	Problem:	C.cpp
	Time:		2020-06-01 23:12
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 3e5 + 10, inf = 1e9;

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

int n, m, k;
int fa[maxn], d[maxn], s[maxn];
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
struct edge
{
	int x, y, z;
	edge(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
	inline bool operator < (const edge &B) const {return z > B.z;}
}E[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	d[1] = d[n + 1] = 2;
	REP(i, 1, n + n - 2)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		if (i >= n) x += n, y += n;
		E[i] = edge(x, y, z);
		d[x]++;d[y]++;
	}
	m = n + n - 2;
	E[++m] = edge(1, n + 1, inf);
	int N = n + n;
	sort(E + 1, E + 1 + m);
	REP(i, 1, N) fa[i] = i, k += (s[i] = (d[i] == 1));
	long long ans = 0, lim = k / 2;
	REP(i, 1, m)
	{
		int x(E[i].x), y(E[i].y);
		x = find(x);y = find(y);
		if (k - s[x] * s[y] > lim)
		{
			k -= s[x] * s[y];
			fa[x] = y;
			s[y] |= s[x];
		}
		else ans += E[i].z;
	}
	cout << ans << endl;
	return 0;
}
