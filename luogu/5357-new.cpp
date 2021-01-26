/*
	Problem:	5357-new.cpp
	Time:		2021-01-26 11:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

namespace AC
{
	int ch[maxn][26], fail[maxn], End[maxn], cur = 1, rt = 1, N;
	void insert(char s[])
	{
		int n = strlen(s + 1), p = 1;
		REP(i, 1, n)
		{
			int c = s[i] - 'a';
			if (!ch[p][c]) ch[p][c] = ++cur;
			p = ch[p][c];
		}
		End[++N] = p;
	}
	void insert()
	{
		static char str[maxn];
		scanf("%s", str + 1);
		insert(str);
	}
	vector <int> G[maxn];
	void build()
	{
		static int que[maxn], head, tail;
		REP(i, 0, 25) ch[0][i] = 1;
		que[head = tail = 0] = 1;
		while (head <= tail)
		{
			int x = que[head++];
			REP(i, 0, 25)
				if (ch[x][i])
				{
					fail[ch[x][i]] = ch[fail[x]][i];
					que[++tail] = ch[x][i];
				}
				else ch[x][i] = ch[fail[x]][i];
		}
		REP(i, 2, cur) G[fail[i]].emplace_back(i);
	}
	int s[maxn];
	void dfs(int u)
	{
		for (int v : G[u])
		{
			dfs(v);
			s[u] += s[v];
		}
	}
	void work(char str[])
	{
		int n = strlen(str + 1), p = 1;
		REP(i, 1, n)
		{
			p = ch[p][str[i] - 'a'];
			s[p]++;
		}
		dfs(1);
		REP(i, 1, N) printf("%d\n", s[End[i]]);
	}
}
char s[2000005];

int main()
{
#ifdef CraZYali
	file("5357-new");
#endif
	REP(i, 1, read<int>())
		AC :: insert();
	AC :: build();
	scanf("%s", s + 1);
	AC :: work(s);
	return 0;
}
