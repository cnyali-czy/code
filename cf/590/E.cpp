/*
	Problem:	E.cpp
	Time:		2021-01-26 11:57
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 800;

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
bool G[maxn][maxn];
char *str[maxn], tmp[10000005];

namespace AC
{
	const int maxn = 1e7 + 10;
	int ch[maxn][2], fail[maxn], End[::maxn], cur = 1, rt = 1, N, id[maxn];
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
		id[p] = N;
	}
	int lst[maxn];
	void build()
	{
		static int que[maxn], head, tail;
		REP(i, 0, 1) ch[0][i] = 1;
		que[head = tail = 0] = 1;
		while (head <= tail)
		{
			int x = que[head++];
			REP(i, 0, 1)
				if (ch[x][i])
				{
					fail[ch[x][i]] = ch[fail[x]][i];
					que[++tail] = ch[x][i];
				}
				else ch[x][i] = ch[fail[x]][i];
			if (id[fail[x]]) lst[x] = fail[x];
			else lst[x] = lst[fail[x]];
		}
		//dfs(1);
		//A -> B A \in B
		REP(i, 1, n) G[i][i] = 1;
		REP(i, 1, n) 
		{
			G[id[lst[End[i]]]][i] = 1;
			G[id[End[i]]][i] = 1;
		}
		REP(i, 1, n)
		{
			int p = 1;
			REP(j, 1, strlen(str[i] + 1))
			{
				p = ch[p][str[i][j] - 'a'];
				G[id[lst[p]]][i] = G[id[p]][i] = 1;
			}
		}
		REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) G[i][j] |= (G[i][k] && G[k][j]);
	}
}
vector <int> B[maxn << 1];
bool vis[maxn << 1], inmat[maxn << 1];
int mat[maxn << 1];

bool dfs(int x)
{
	for (int y : B[x]) if (!vis[y])
	{
		vis[y] = 1;
		if (!mat[y] || dfs(mat[y]))
		{
			mat[y] = x;
			return 1;
		}
	}
	return 0;
}

void dfs2(int x)
{
	if (vis[x]) return;
	vis[x] = 1;
	for (int y : B[x]) if (mat[y] != x)
	{
		vis[y] = 1;
		dfs2(mat[y]);
	}
}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	REP(i, 1, n = read<int>())
	{
		scanf("%s", tmp + 1);
		AC :: insert(tmp);
		str[i] = new char[strlen(tmp + 1) + 5];
		REP(j, 1, strlen(tmp + 1)) str[i][j] = tmp[j];
		str[i][strlen(tmp + 1) + 1] = '\0';
	}
	AC :: build();
	REP(i, 1, n) REP(j, 1, n) if (i ^ j && G[i][j])
		B[i].emplace_back(j + n);
	int tot = 0;
	REP(i, 1, n)
	{
		memset(vis, 0, sizeof vis);
		if (dfs(i)) tot++;
	}
	memset(vis, 0, sizeof vis);
	REP(i, 1, n + n) inmat[mat[i]] = 1;
	REP(i, 1, n) if (!inmat[i] && !vis[i]) dfs2(i);
	vector <int> ans;
	REP(i, 1, n) if (vis[i] && !vis[i + n]) ans.emplace_back(i);
	cout << ans.size() << endl;
	REP(i, 0, (int)ans.size() - 1) printf("%d%c", ans[i], i == end_i ? '\n' : ' ');
	return 0;
}
