/*
	Problem:	A.cpp
	Time:		2021-03-12 07:48
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 2e5 + 10;

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

int n, a[maxn], b[maxn];
int fa[maxn], siz[maxn], mx[maxn];
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x != y)
	{
		fa[x] = y;
		siz[y] += siz[x];
		mx[y] = max(mx[y], mx[x]);
	}
	siz[y]--;
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n;
	static int c[maxn << 2];int m = 0;
	int ans = 0;
	REP(i, 1, n)
	{
		c[++m] = a[i] = read<int>();
		c[++m] = b[i] = read<int>();
		ans += a[i] + b[i];
	}
	sort(c + 1, c + 1 + m);
	m = unique(c + 1, c + 1 + m) - c - 1;
	REP(i, 1, m)
	{
		ans -= c[i];
		fa[i] = i;
		siz[i] = 1;
		mx[i] = i;
	}
	REP(i, 1, n)
	{
		a[i] = lower_bound(c + 1, c + 1 + m, a[i]) - c;
		b[i] = lower_bound(c + 1, c + 1 + m, b[i]) - c;
		uni(a[i], b[i]);
	}
	REP(i, 1, m) if (i == fa[i] && siz[i]) ans += c[mx[i]];
	cout << ans << endl;
	
	return 0;
}
