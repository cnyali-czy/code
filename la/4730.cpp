#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define chkmax(a, b) a = max(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid  
#define rson rs, mid + 1, r  

using namespace std;
const int maxn = 2000080, maxm = 100010;

int rank1[maxm], miny[maxm], maxy[maxm], y[maxm];

int fa[maxm];
inline int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
  
struct ST
{
	int l, r, add, city;
}st[maxn << 2];

void build(int p, int l, int r)
{
	st[p].l = l, st[p].r = r;
	st[p].add = st[p].city = 0;
	if (l == r) return;

	build(lson);
	build(rson);
}  
  
inline void pushdown(int p)  
{
	if (st[p].add)
	{
		st[ls].add += st[p].add;
		st[rs].add += st[p].add;
		st[p].add = 0;
	}
	if (st[p].city)
	{
		st[ls].city += st[p].city;
		st[rs].city += st[p].city;
		st[p].city = 0;
	}
}

inline void update(int p, int l, int r, int add, int c)
{  
	if (st[p].l == l && st[p].r == r)
	{
		st[p].add += add;
		st[p].city += c;
		return;
	}
	pushdown(p);
	if (st[ls].r >= r)
		update(ls, l, r, add, c);
	else if (st[rs].l <= l)
		update(rs, l, r, add, c);
	else   
	{
		update(ls, l, st[ls].r, add, c);
		update(rs, st[rs].l, r, add, c);
	}
}
  
inline void uni(int a,int b)  
{  
	int _fa = find(a), fb = find(b);
	if (_fa == fb) return;
	if (rank1[_fa] > 1)
		update(1,miny[_fa],maxy[_fa],-1,-rank1[_fa]);
	if (rank1[fb] > 1)  
		update(1,miny[fb],maxy[fb],-1,-rank1[fb]);
	fa[_fa] = fb;
	rank1[fb] += rank1[_fa];
	miny[fb] = min(miny[_fa],miny[fb]);
	maxy[fb] = max(maxy[_fa],maxy[fb]);
	update(1,miny[fb],maxy[fb],1,rank1[fb]);
}

inline void init(int n)
{  
	REP(i, 0, n - 1)
	{  
		fa[i] = i;  
		rank1[i] = 1;  
		miny[i] = maxy[i] = y[i];  
	}  
}  
  
inline int query(int p, int pos)
{  
	if (st[p].l == pos && st[p].r == pos) return p; 
	pushdown(p);
	return st[ls].r >= pos ? query(ls, pos) : query(rs, pos);
}  

int n, m, k, u, v, len;
char SSS[10];
double c;

int main()
{
#ifdef CraZYali
	freopen("4730.in", "r", stdin);
	freopen("4730.out", "w", stdout);
#endif
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		REP(i, 0, n - 1)
		{
			scanf("%*d%d",y + i);
			y[i] <<= 1;
			chkmax(len, y[i]);
		}
		init(n);
		build(1, 0, len);

		scanf("%d", &m);
		while(m--)
		{
			scanf("%s", SSS + 1);
			if (SSS[1] == 'r')
			{
				scanf("%d%d", &u, &v);
				uni(u,v);
			}
			else
			{
				scanf("%lf", &c);
				c *= 2;
				if (c > len)
				{
					printf("0 0\n");
					continue;
				}
				int pos = query(1, (int)c);
				printf("%d %d\n",st[pos].add, st[pos].city);
			}
		}
	}
	return 0;
}
