/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.05 10:04
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

const int sig = 26;
int siz[maxn], fail[maxn], ch[maxn][sig], len[maxn], cur = 1, lst = 1;
inline int newnode(int len)
{
	::len[++cur] = len;
	return cur;
}
inline void extend(int c)
{
	int v = lst, u = newnode(len[v] + 1);
	siz[u] = 1;
	for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
	if (!v) fail[u] = 1;
	else if (len[v] + 1 == len[ch[v][c]]) fail[u] = ch[v][c];
	else
	{
		int Old(ch[v][c]), New(newnode(len[v] + 1));
		copy(ch[Old], ch[Old] + sig, ch[New]);
		fail[New] = fail[Old];
		fail[Old] = fail[u] = New;
		for (; ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
	}
	lst = u;
}

char s[maxn];
int n, q;
vector <int> G[maxn];
void dfs(int u)
{
	for (auto v : G[u])
	{
		dfs(v);
		siz[u] += siz[v];
	}
}
vector <int> vis;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	REP(i, 1, n) extend(s[i] - 'a');
	REP(i, 2, cur) G[fail[i]].emplace_back(i);
	dfs(1);
	q = read<int>();
	while (q--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		REP(i, 1, n) s[i + n] = s[i];
		int p = 1, ard = 0;
		REP(i, 1, n + n - 1)
		{
			int c = s[i] - 'a';
			while (p && !ch[p][c]) ard = len[p = fail[p]];
			if (ch[p][c])
			{
				p = ch[p][c];
				ard++;
			}
			while (len[fail[p]] >= n) ard = len[p = fail[p]];
			if (ard >= n) vis.emplace_back(p);
		}
		long long ans = 0;
		sort(vis.begin(), vis.end());
		vis.resize(unique(vis.begin(), vis.end()) - vis.begin());
		for (auto i : vis) ans += siz[i];
		cout << ans;putchar(10);
		vis.clear();
	}
	return 0;
}
