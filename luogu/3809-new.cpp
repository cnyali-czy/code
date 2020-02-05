/*
 * File Name:	3809-new.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.05 15:25
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e6 + 10;

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

const int sig = 10 + 26 + 26 + 1;
inline int _to(char c)
{
	if (isdigit(c)) return c - 48;
	else if ('A' <= c && c <= 'Z') return c - 'A' + 10;
	else return c - 'a' + 36;
}
inline int to(char c) {return 1 + _to(c);}
int len[maxn], fail[maxn], ch[maxn][sig], lst = 1, cur = 1, id[maxn];
inline int newnode(int l, int i)
{
	++cur;
	len[cur] = l;
	id[cur] = i;
	return cur;
}
bool good[maxn];
inline void extend(int c, int id)
{
	int v = lst, u = newnode(len[v] + 1, id);
	good[u] = 1;
	for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
	if (!v) fail[u] = 1;
	else if (len[v] + 1 == len[ch[v][c]]) fail[u] = ch[v][c];
	else
	{
		int Old(ch[v][c]), New(newnode(len[v] + 1, id));
		copy(ch[Old], ch[Old] + sig, ch[New]);
		fail[New] = fail[Old];
		fail[Old] = fail[u] = New;
		for (; v && ch[v][c] == Old;v = fail[v]) ch[v][c] = New;
	}
	lst = u;
}

int n;
vector <pair <int, int> > G[maxn];
char s[maxn];

void dfs(int x)
{
	if (good[x]) printf("%d ", id[x]);
	for (auto y : G[x]) dfs(y.second);
}
int main()
{
#ifdef CraZYali
	file("3809-new");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	DEP(i, n, 1) extend(s[i] = to(s[i]), i);
	REP(i, 2, cur) G[fail[i]].emplace_back(s[id[i] + len[fail[i]]], i);
	REP(i, 1, cur) sort(G[i].begin(), G[i].end());
	dfs(1);
	return 0;
}
