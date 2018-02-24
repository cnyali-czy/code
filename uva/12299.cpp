#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 100000 + 10, inf = 100000;

int m, n, k;

#define ls p << 1
#define rs p << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
struct seg_T
{
	int Min[maxn << 2];
	inline void build(int p, int l, int r)
	{
		if (l == r) scanf("%d", Min + p);
		else
		{
			build(lson);
			build(rson);
			Min[p] = min(Min[ls], Min[rs]);
		}
	}
	inline int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R || l == r) return Min[p];
		else
		{
			int x, y;x = y = inf;
			if (L <= mid) x = query(lson, L, R);
			if (R >  mid) y = query(rson, L, R);
			return min(x, y);
		}
	}
	inline void update(int p, int l, int r, int x, int y)
	{
		if (l == r && l == x) Min[p] = y;
		else
		{
			if (x <= mid)	update(lson, x, y);
			else			update(rson, x, y);
			Min[p] = min(Min[ls], Min[rs]);
		}
	}
}T;

vector <int> v;

int main()
{
#ifdef CraZYali
	freopen("stderr", "w", stderr);
	freopen("12299.in", "r", stdin);
	freopen("12299.out", "w", stdout);
#endif
	scanf("%d %d\n", &n, &m);
	T.build(1, 1, n);
	scanf("\n");

	char c;
	while (m--)
	{
		c = getchar();
		if (c == 'q')
		{
			int x, y;
			scanf("uery(%d,%d)\n", &x, &y);
			printf("%d\n", T.query(1, 1, n, x, y));
		}
		else
		{
			scanf("hift(");
			v.clear();
			int temp, siz;

			while (scanf("%d", &temp) != EOF)
			{
				v.push_back(temp);
				c = getchar();
				if (c == ')') break;
			}
			c = getchar();

			siz = v.size() - 2;
			temp = T.query(1, 1, n, v[0], v[0]);
			REP(i, 0, siz) T.update(1, 1, n, v[i], T.query(1, 1, n, v[i + 1], v[i + 1]));
			T.update(1, 1, n, v[siz + 1], temp);
		}
	}
	return 0;
}
