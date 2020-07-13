#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define i64 long long

using namespace std;
const int maxn = 2e6 + 10;

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

int ch[maxn][26], fail[maxn], q[maxn], head, tail, cur, fa[maxn];
i64 w[maxn], g[maxn], f[maxn], ans, h[maxn];
char str[maxn];
void insert(int v)
{
	int p = 0;
	REP(i, 1, strlen(str + 1))
	{
		int c = str[i] - 'a';
		if (!ch[p][c]) fa[ch[p][c] = ++cur] = p;
		p = ch[p][c];
	}
	w[p] += v;
}

void build()
{
	tail = -1;
	REP(i, 0, 25) if (ch[0][i]) q[++tail] = ch[0][i];
	while (head <= tail)
	{
		int u = q[head++];
		w[u] += w[fail[u]];
		g[u] = g[fa[u]] + w[u];
		if (!fail[u]) h[u] = h[fa[u]];
		else
		{
			h[u] = -1e15;
			for (int i = fa[u]; i != fa[fail[u]]; i = fail[i])
				chkmax(h[u], h[i] + w[fail[u]]);
		}
		f[u] = max(f[fail[u]], max(g[u], h[u]));
		REP(i, 0, 25)
			if (ch[u][i])
			{
				fail[ch[u][i]] = ch[fail[u]][i];
				q[++tail] = ch[u][i];
			}
			else ch[u][i] = ch[fail[u]][i];
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		scanf("%s", str + 1);
		insert(read<int>());
	}
	scanf("%s", str + 1);
	insert(0);
	build();
	int p = 0;
	REP(i, 1, m)
	{
		p = ch[p][str[i] - 'a'];
		chkmax(ans, f[p]);
	}
	cout << ans << endl;
	return 0;
}
