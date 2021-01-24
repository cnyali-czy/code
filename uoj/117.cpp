/*
	Problem:	117.cpp
	Time:		2021-01-22 08:22
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
const int maxn = 1e5 + 10, maxm = 2e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
int in[maxn], out[maxn], d[maxn];

void add(int x, int y)
{
	out[x]++;in[y]++;
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int t, n, m;

bool del[maxm << 1];
int cur[maxn];
int stk[maxm], top;
void dfs(int x)
{
	for (int &i = cur[x]; i; i = ne[i]) if (!del[i])
	{
		del[i] = 1;
		if (t == 1) del[i ^ 1] = 1;
		int c = i;
		dfs(to[i]);
		stk[++top] = c;
	}
}

int main()
{
#ifdef CraZYali
	file("117");
#endif
	t = read<int>();
	n = read<int>();m = read<int>();
	REP(i, 1, m)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);if (t == 1) add(y, x);
		d[x]++;d[y]++;
	}
	if (t == 1)
	{
		REP(i, 1, n) if (d[i] & 1)
		{
			puts("NO");
			return 0;
		}
	}
	else
	{
		REP(i, 1, n) if (in[i] ^ out[i])
		{
			puts("NO");
			return 0;
		}
	}
	REP(i, 1, n) cur[i] = bg[i];
	dfs(to[2]);
	if (top ^ m) puts("NO");
	else
	{
		puts("YES");
		DEP(i, m, 1)
		{
			int E = stk[i];
			if (t == 1) printf("%d ", (E & 1 ? -1 : 1) * (E >> 1));
			else printf("%d ", E - 1);
		}
	}
	
	return 0;
}
