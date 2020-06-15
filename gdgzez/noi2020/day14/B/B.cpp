/*
	Problem:	B.cpp
	Time:		2020-06-15 15:48
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50 + 5, N = 500 + 5, M = 2e5 + 10;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

namespace AC
{
	char ch[N][26], fail[N], rt = -1, cur = -1, s[N];
	void insert(char &p, char *c, int less)
	{
		if (p == -1) p = ++cur;
		if (!less) return void(s[p]++);
		insert(ch[p][(*c) - 'a'], c + 1, less - 1);
	}
	char q[N], head, tail;
	void build()
	{
		head = 0;tail = -1;
		REP(i, 0, 25)
			if (ch[rt][i] == -1) ch[rt][i] = rt;
			else q[++tail] = ch[rt][i];
		while (head <= tail)
		{
			int x = q[head++];
			s[x] += s[fail[x]];
			REP(i, 0, 25)
				if (ch[x][i] == -1) ch[x][i] = ch[fail[x]][i];
				else
				{
					fail[ch[x][i]] = ch[fail[x]][i];
					q[++tail] = ch[x][i];
				}
		}
//		REP(i, 0, cur) printf("%d%c",fail[i],i==end_i?'\n':' ');
//		REP(i, 0, cur) REP(j, 0, 25) printf("%d%c",ch[i][j],j==25?'\n':' ');
	}
}
char str[M];
int len[M], bg[M], lent[M], cnt;
const int ccc = 18;
struct info
{
	int sta;
	inline int tar() {return sta & 63;}
	inline int mat() {return sta >> 6;}
	inline void tar(int x) {sta = (sta >> 6) << 6 | x;}
	inline void mat(int x) {sta = (x << 6) + tar();}
	inline void make(int x, int y)
	{
		sta = 0;
		tar(x);
		mat(y);
	}
	inline info operator + (info B)
	{
		info tmp;tmp.sta = 0;
		tmp.tar(B.tar());
		tmp.mat(mat() + B.mat());
		return tmp;
	}
}g[ccc][maxn][M], f[M << 2][maxn];
void New(int id, int lft)
{
	scanf("%s", str);
	len[id] = strlen(str);
	lent[id] = lent[id - 1] + len[id - 1];
	bg[id] = lft;
	REP(x, 0, AC :: cur) REP(i, 0, len[id] - 1)
		g[0][x][i + lent[id]].make(AC :: ch[x][str[i] - 'a'], AC :: s[AC :: ch[x][str[i] - 'a']]);
	REP(k, 1, ccc - 1) REP(x, 0, AC :: cur) REP(i, 0, len[id] - 1)
	{
		int y = g[k - 1][x][i + lent[id]].tar();
		int nxt = (i + (1 << k - 1)) % len[id];
		g[k][x][i + lent[id]] = g[k - 1][x][i		+ lent[id]] + g[k - 1][y][nxt + lent[id]];
		/*
		g[k][x][i + lent[id]].tar(	g[k - 1][y][nxt + lent[id]].tar());
		g[k][x][i + lent[id]].mat(	g[k - 1][y][nxt + lent[id]].mat() +
									g[k - 1][x][i	+ lent[id]].mat());
									*/
	}
}
int lev[M << 2], tag[M << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
void pushup(int p)
{
	REP(i, 0, AC :: cur)
	{
		int nxt = f[ls][i].tar();
		f[p][i] = f[ls][i] + f[rs][nxt];
/*
		f[p][i].tar(f[rs][nxt].tar());
		f[p][i].mat(f[ls][i].mat() + f[rs][nxt].mat());
		*/
	}
}
inline void maintain(int p, int l, int r, int id)
{
	REP(i, 0, AC :: cur)
		f[p][i] = g[lev[p]][i][(l - bg[id]) % len[id] + lent[id]];
	tag[p] = id;
}
inline void pushdown(int p, int l, int r)
{
	maintain(lson, tag[p]);
	maintain(rson, tag[p]);
	tag[p] = 0;
}
void build(int p, int l, int r)
{
	if (l == r) return;
	build(lson);build(rson);
	lev[p] = lev[ls] + 1;
}
void update(int p, int l, int r, int L, int R, int v)
{
	if (L <= l && r <= R) maintain(p, l, r, v);
	else
	{
		if (tag[p]) pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, v);
		if (R >  mid) update(rson, L, R, v);
		pushup(p);
	}
}
int ne, ans;
void query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		ans += f[p][ne].mat();
		ne = f[p][ne].tar();
	}
	else
	{
		if (tag[p]) pushdown(p, l, r);
		if (L <= mid) query(lson, L, R);
		if (R >  mid) query(rson, L, R);
	}
}
int n, q;

int main()
{
#ifdef CraZYali
	file("B");
#endif
	memset(AC :: ch, -1, sizeof AC :: ch);
	n = read<int>();q = read<int>();
	REP(i, 1, n)
	{
		scanf("%s", str);
		AC :: insert(AC :: rt, str, strlen(str));
	}
	AC :: build();
	New(cnt = 1, 1);
	int m = 1;
	while (m < len[1]) m <<= 1;
	build(1, 1, m);
	maintain(1, 1, m, 1);
	while (q--)
	{
		int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 1)
		{
			New(++cnt, l);
			update(1, 1, m, l, r, cnt);
		}
		else
		{
			ne = AC :: rt;
			ans = 0;
			query(1, 1, m, l, r);
			printf("%d\n", ans);
		}
	}
	return 0;
}
