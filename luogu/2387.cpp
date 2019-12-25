//稍微写点注释吧
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100000 + 10, maxm = 200000 + 10, maxN = maxn + maxm;

	template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
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
struct Edge
{
	int x, y, a, b;
	inline bool operator < (Edge B) const {return b < B.b;}
}E[maxN];

int n, m;

int f[maxN];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}
inline void uni(int x, int y) {f[find(x)] = find(y);}

int fa[maxN], ch[maxN][2], s[maxN];
bool tag[maxN];
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
#define get(x) (rs(fa[x]) == x)
#define notroot(x) (ls(fa[x]) == x || rs(fa[x]) == x)

inline void pushup(int x)
{
	s[x] = x;s[0] = 0;
	if (E[s[x]].a < E[s[ls(x)]].a) s[x] = s[ls(x)];
	if (E[s[x]].a < E[s[rs(x)]].a) s[x] = s[rs(x)];//把最大的边pushup上来
}

inline void rotate(int x)
{
	int y(fa[x]), z(fa[y]);
	bool k(get(x));
	if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
	ch[y][k] = ch[x][k ^ 1];
	if (notroot(y)) ch[z][get(y)] = x;
	fa[x] = fa[y];
	fa[y] = x;
	ch[x][k ^ 1] = y;
	pushup(y);pushup(x);
}

inline void pushdown(int x)
{
	if (!tag[x]) return;
	swap(ls(x), rs(x));
	tag[ls(x)] ^= 1;tag[rs(x)] ^= 1;
	tag[x] = 0;
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
void access(int x)
{
	for (register int y = 0; x; x = fa[y = x])
	{
		splay(x);
		rs(x) = y;
		pushup(x);
	}
}
inline void makeroot(int x)
{
	access(x);
	splay(x);
	tag[x] ^= 1;
}
inline void link(int x, int y)
{
	makeroot(x);
	fa[x] = y;
}
inline void cut(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
	fa[x] = ls(y) = 0;
}
inline int query(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
	return s[v];
}
const long long inf = 1ll << 60;
long long ans = inf;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int main()
{
#ifdef CraZYali
	file("2387");
#endif
	cin >> n >> m;
	REP(i, 1, n) f[i] = i;
	REP(i, n + 1, n + m)
	{
		E[i].x = read<int>();
		E[i].y = read<int>();
		E[i].a = read<int>();
		E[i].b = read<int>();
	}
	sort(E + n + 1, E + 1 + n + m);
	//大概和边转点差不多，感性理解
	REP(i, n + 1, n + m)
	{
		if (find(E[i].x) ^ find(E[i].y))//不在一个环上，直接link完事
		{
			uni(E[i].x, E[i].y);
			link(E[i].x, i);
			link(E[i].y, i);
		}
		else
		{
			int pos = query(E[i].x, E[i].y);//找到环上最大的边
			if (E[pos].a <= E[i].a) continue;//最大的比这个还小，问题有点大
			//把 老 边 干 翻
			cut(E[pos].x, pos);
			cut(E[pos].y, pos);
			link(E[i].x, i);
			link(E[i].y, i);
		}
		if (find(1) == find(n))//这个时候联通，那很好
		{
			long long int v = E[query(1, n)].a;
			chkmin(ans, v + E[i].b);
		}
	}
	cout << (ans < inf ? ans : -1) << endl;
	return 0;
}
