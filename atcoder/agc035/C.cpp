/*
	Problem:	5140.cpp
	Time:		2021-01-29 10:47
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

using namespace std;
const int maxn = 1e5 + 10;

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

int n;
/*
vector <int> G[maxn];
bool flag;int rt;
void dfs(int x, int y = 0, int fa = 0 )
{
	if (x > n) y ^= (x - n);
	else y ^= x;
	if (x == rt + n && y == rt) {flag = 1;return;}
	for (int z : G[x]) {if (z ^ fa) dfs(z, y, x);if (flag) return;}
}
*/
inline void add(int x, int y) {printf("%d %d\n", x, y);}
int main()
{
#ifdef CraZYali
	file("5140");
#endif
	n = read<int>();
	if (n == (n & -n))
	{
		puts("No");
		return 0;
	}
	puts("Yes");
	add(1, 2);add(2, 3);
	add(n + 1, n + 2);add(n + 2, n + 3);
	add(3, n + 1);
	for (int l = 4; l < n; l += 2)
	{
		add(l, l + 1);
		add(l, 1);
		add(1, l + n + 1);
		add(l + n, l + 1 + n);
	}
	if (n % 2 == 0)
	{
		REP(i, 2, n - 1) if (i % 2 == 0)
		{
			int j = n ^ 1 ^ i;
			if (j < n)
			{
				add(n, i);
				add(n + j, n + n);
				break;
			}
		}
	}
	return 0;
}
