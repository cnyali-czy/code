#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

int n, q;
int ch[maxn][2], fa[maxn], v[maxn], s[maxn], t[maxn], li[maxn];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (rs(fa[x]) == x)
#define notroot(x) (ls(fa[x]) == x || rs(fa[x]) == x)

inline void pushup(int x)
{
	s[x] = s[ls(x)] + s[rs(x)] + li[x] + 1;
}
void rotate(int x)
{
	int y = fa[x], z = fa[y], k = get(x);
	if (ch[x][!k]) fa[ch[x][!k]] = y;
	ch[y][k] = ch[x][!k];
	fa[x] = z;
	if (notroot(y)) ch[z][get(y)] = x;
	ch[x][!k] = y;
	fa[y] = x;
	pushup(y);pushup(x);
}
void pushdown(int x)
{
	if (!t[x]) return;
	swap(ls(x), rs(x));
	if (ls(x)) t[ls(x)] ^= 1;
	if (rs(x)) t[rs(x)] ^= 1;
	t[x] = 0;
}
void pushall(int x)
{
	if (notroot(x)) pushall(fa[x]);
	pushdown(x);
}
void splay(int x)
{
	pushall(x);
	while (notroot(x))
	{
		int y = fa[x];
		if (notroot(y)) rotate(get(x) == get(y) ? y : x);
		rotate(x);
	}
}
int access(int x) // return splay root
{
	int y = 0;
	for (; x; x = fa[y = x])
	{
		splay(x);
		li[x] += s[rs(x)];
		li[x] -= s[rs(x) = y];
	}
	return y;
}
int makeroot(int x) // not splay root, but return it
{
	t[x = access(x)] ^= 1;
	return x;
}
void link(int x, int y)
{
	x = makeroot(x);
	access(y);splay(y);
	fa[x] = y;li[y] += s[x];s[y] += s[x];
//	pushup(y);
}
int read()
{
	register char c = getchar();
	int res = 0;
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}
int main()
{
#ifdef CraZYali
	freopen("4219.in", "r", stdin);
	freopen("4219.out", "w", stdout);
#endif
	n = read(); q = read();
	REP(i, 1, n) s[i] = 1;
	while (q--)
	{
		register char c = getchar();
		while (!isalpha(c)) c = getchar();
		int x = read(), y = read();
		if (c == 'Q')
		{
			int N = s[makeroot(x)];
			access(y);
			int sy = li[y] + 1;
			printf("%lld\n", 1ll * sy * (N - sy));
		}
		else link(x, y);
	}
	return 0;
}
