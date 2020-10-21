/*
	Problem:	A.cpp
	Time:		2020-10-21 11:35
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <queue>

using namespace std;
const int maxm = 500 * 500;

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

string res, st[500];
int n, m;
map <string, int> id;

void dfs(int x, int lst)
{
	if (x == 7)
	{
		st[id[res] = ++n] = res;
//		printf("%s %d\n", res.c_str(), n);
		return;
	}
	x++;
	REP(i, lst, 4)
	{
		res[x] = i + 48;
		dfs(x, i);
	}
}

int sg[maxm], in[maxm];
vector <int> G[maxm];
inline int Id(int x, int y) {return (x - 1) * n + y;}
void init()
{
	res = "00000000";
	dfs(-1, 0);
	REP(i, 1, n) REP(j, 1, n) if (i + j > 1)
	{
		int pzk = Id(i, j);
		REP(A, 0, 7) if (st[i][A] > '0') REP(B, 0, 7) if (st[j][B] > '0')
		{
			char c = (st[i][A] - '0' + st[j][B] - '0') % 5 + '0';
			auto New1 = st[i];New1[A] = c;
			sort(New1.begin(), New1.end());
			G[Id(j, id[New1])].emplace_back(pzk);
		}
	}
	int m = Id(n, n);
	REP(i, 1, m) G[i].resize(unique(G[i].begin(), G[i].end()) - G[i].begin());
	REP(i, 1, m) for (int j : G[i]) in[j]++;
	memset(sg, -1, sizeof sg);
	queue <int> q;
	sg[1] = 1;
	static bool vis[maxm];
	vis[1] = 1;
	q.emplace(1);
	assert(!in[1]);
	REP(i, 2, n)
	{
		sg[Id(1, i)] = 1;
		sg[Id(i, 1)] = 0;
		q.emplace(Id(1, i));
		q.emplace(Id(i, 1));
		vis[Id(1, i)] = vis[Id(i, 1)] = 1;
#ifdef CraZYali
		assert(!in[Id(1,i)]);
		assert(!in[Id(i,1)]);
#endif
	}

	while (!q.empty())
	{
		int u = q.front();q.pop();
		if (sg[u] == -1) sg[u] = 0;
		for (int v : G[u]) 
		{
			if (sg[u] == 0)
			{
				sg[v] = 1;
				if (!vis[v]) vis[v] = 1, q.emplace(v);
			}
			if (!(--in[v])) if (!vis[v]) vis[v] = 1, q.emplace(v);
		}
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	init();
	REP(T, 1, read<int>())
	{
		string s = "00000000", t = "00000000";
		int opt = read<int>();
		REP(i, 0, 7) s[i] = read<int>() + 48;
		REP(i, 0, 7) t[i] = read<int>() + 48;
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		if (s == "00000000")
		{
			puts("Alice");
			continue;
		}
		if (t == "00000000")
		{
			puts("Bob");
			continue;
		}
		if (opt) swap(s, t);
		int num = Id(id[s], id[t]);
		if (sg[num] == 1) puts(opt ? "Bob" : "Alice");
		else if (!sg[num]) puts(opt ? "Alice" : "Bob");
		else puts("Deal");
	}
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
