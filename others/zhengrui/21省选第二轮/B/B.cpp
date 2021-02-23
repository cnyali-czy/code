/*
	Problem:	B.cpp
	Time:		2021-02-20 09:14
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50000 + 10, maxq = 1e5 + 10;

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

int n, q;
string str[maxn];
int Len[maxn];

unordered_map <int, int> mem[maxn];

int ch[maxn << 1][26], len[maxn << 1], fail[maxn << 1], lst, cur;
void init()
{
	REP(i, 1, cur)
	{
		memset(ch[i], 0, sizeof ch[i]);
		fail[i] = len[i] = 0;
	}
	lst = cur = 1;
}
void extend(int c)
{
	int u = ++cur, v = lst;lst = u;
	len[u] = len[v] + 1;
	for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
	if (!v) fail[u] = 1;
	else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
	else
	{
		int New(++cur), Old(ch[v][c]);
		copy(ch[Old], ch[Old] + 26, ch[New]);
		len[New] = len[v] + 1;
		fail[New] = fail[Old];
		fail[Old] = fail[u] = New;
		for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
	}
}

void build(int y)
{
	init();
	for (auto c : str[y]) extend(c - 'a');
}
int bf(int x)
{
	int l = 0, ans = 0, p = 1;
	for (auto c : str[x])
	{
		while (p > 1 && !ch[p][c - 'a']) p = fail[p], l = len[p];
		if (ch[p][c - 'a'])
		{
			p = ch[p][c - 'a'];
			l++;
		}
		ans = max(ans, l);
	}
	return ans;
}
vector <int> qry[maxn];
int ans[maxq];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> q;
	REP(i, 0, n - 1) cin >> str[i];
	static int x[maxq], y[maxq];
	REP(i, 1, q)
	{
		x[i] = read<int>();y[i] = read<int>();
		int &u = x[i], &v = y[i];
		if (make_pair(Len[u], u) < make_pair(Len[v], v)) swap(u, v);
		qry[u].emplace_back(v);
	}
	REP(i, 0, n - 1) if (qry[i].size())
	{
		sort(qry[i].begin(), qry[i].end());
		qry[i].resize(unique(qry[i].begin(), qry[i].end()) - qry[i].begin());
		build(i);
		for (auto j : qry[i]) mem[i][j] = bf(j);
	}
	REP(i, 1, q) printf("%d\n", mem[x[i]][y[i]]);
	return 0;
}
