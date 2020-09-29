/*
	Problem:	bf.cpp
	Time:		2020-09-22 20:29
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

using namespace std;
const int maxn = 10;

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

int n, k;
int fa[maxn], d, ans[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void add(int x, int y)
{
	fa[find(x)] = find(y);
	if (x == 1 || y == 1) d++;
}
void work(int N)
{
	n = N;
	REP(i, 0, n) ans[i] = 0;
	int c2 = N * (N - 1) / 2;
	REP(S, 1, (1 << c2) - 1)
	{
		int c = 0;
		d = 0;
		REP(i, 1, n) fa[i] = i;
		REP(i, 1, n) REP(j, i + 1, n)
		{
			if (S >> c & 1) add(i, j);
			c++;
		}
		bool flag = 1;
		REP(i, 2, n) if (find(i) ^ find(1)) {flag = 0;break;}
		if (flag) ans[d]++;
	}
	REP(i, 1, n) printf("%d%c", ans[i], i == end_i ? '\n' : ' ' );
}

int main()
{
	file("bf");
	REP(i, 1, 7) work(i);
	return 0;
}

