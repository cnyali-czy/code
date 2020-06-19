/*
	Problem:	5357.cpp
	Time:		2020-06-19 18:47
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;
char t[maxn], s[2000005];

int ch[maxn][26], cur = 1, mat[maxn], siz[maxn], fail[maxn];
int q[maxn], head, tail;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
}
int main()
{
#ifdef CraZYali
	file("5357");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		scanf("%s", t + 1);
		int p = 1;
		REP(j, 1, strlen(t + 1))
		{
			int c = t[j] - 'a';
			if (!ch[p][c]) ch[p][c] = ++cur;
			p = ch[p][c];
		}
		mat[i] = p;
	}
	REP(i, 0, 25) ch[0][i] = 1;
	q[head = tail = 0] = 1;
	while (head <= tail)
	{
		int x = q[head++];
		REP(i, 0, 25)
			if (ch[x][i])
			{
				fail[ch[x][i]] = ch[fail[x]][i];
				q[++tail] = ch[x][i];
			}
			else ch[x][i] = ch[fail[x]][i];
	}
	scanf("%s", s + 1);
	int p = 1;
	REP(i, 1, strlen(s + 1))
	{
		p = ch[p][s[i] - 'a'];
		siz[p]++;
	}
	REP(i, 2, cur) add(fail[i], i);
	dfs(1);
	REP(i, 1, n) printf("%d\n", siz[mat[i]]);
	return 0;
}
