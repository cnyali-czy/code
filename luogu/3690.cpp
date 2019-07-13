#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3e5 + 10, maxm = 3e5 + 10;

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

int fa[maxn], ch[maxn][2], val[maxn], s[maxn], st[maxn], top;
bool tag[maxn];
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
bool notroot(int x) {return ls(fa[x]) == x || rs(fa[x]) == x;}
void pushup(int x) {s[x] = s[ls(x)] ^ s[rs(x)] ^ val[x];}
void reverse(int x) {swap(ls(x), rs(x));tag[x] ^= 1;}
void pushdown(int x)
{
	if (tag[x])
	{
		reverse(ls(x));
		reverse(rs(x));
		tag[x] = 0;
	}
}
void rotate(int x)
{
	int y = fa[x], z = fa[y], k = (rs(y) == x), w = ch[x][k ^ 1];
	if (notroot(y)) ch[z][rs(z) == y] = x;
	ch[x][k ^ 1] = y;
	ch[y][k] = w;
	if (w) fa[w] = y;
	fa[y] = x;fa[x] = z;
	pushup(y);
}
void splay(int x)
{
	int y = x, z(0);
	st[++top] = y;
	while (notroot(y)) st[++top] = y = fa[y];
	while (top) pushdown(st[top--]);
	while (notroot(x))
	{
		y = fa[x];z = fa[y];
		if (notroot(y)) rotate((ls(y) == x) ^ (ls(z) == x) ? x : y);
		rotate(x);
	}
	pushup(x);
}
void access(int x)
{
	for (int y = 0; x ; x = fa[y = x]) splay(x), rs(x) = y, pushup(x);
}
void makeroot(int x)
{
	access(x);
	splay(x);
	reverse(x);
}
int findroot(int x)
{
	access(x);
	splay(x);
	while (ls(x)) pushdown(x), x = ls(x);
	splay(x);
	return x;
}
void split(int x, int y)
{
	makeroot(x);
	access(y);splay(y);
}
void link(int x, int y)
{
	makeroot(x);
	if (findroot(y) != x) fa[x] = y;
}
void cut(int x, int y)
{
	makeroot(x);
	if (findroot(y) == x && fa[y] == x && !ls(y))
	{
		fa[y] = rs(x) = 0;
		pushup(x);
	}
}
int m, n, k;

int main()
{
#ifdef CraZYali
	file("3690");
#endif
	cin >> n >> m;
	REP(i, 1, n) val[i] = read<int>();
	while (m--)
	{
		int opt = read<int>(), x = read<int>(), y = read<int>();
		switch (opt)
		{
			case 0:split(x, y);printf("%d\n", s[y]);break;
			case 1:link(x, y);break;
			case 2:cut(x, y);break;
			case 3:splay(x);val[x] = y;
		}
	}
	return 0;
}
