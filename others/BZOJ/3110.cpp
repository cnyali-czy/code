#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <cstdio>
#include <iostream>

using namespace std;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

#define mid (l + r >> 1)
#define lson p -> ls, l, mid
#define rson p -> rs, mid + 1, r

int n, m;

struct node_inside
{
	node_inside *ls, *rs;
	int sum, tag;
	node_inside() : sum(0), tag(0), ls(NULL), rs(NULL) {}
};
int query(node_inside *x, bool flag = 1) {return x != NULL ? x -> sum * flag + x -> tag * (flag ^ 1) : 0;}
void update(node_inside *&p, int l, int r, int L, int R)
{
	if (p == NULL) p = new node_inside();
	if (L == l && r == R) p -> tag++;
	else
		if (L >  mid) update(rson, L, R);
		else if (R <= mid) update(lson, L, R);
		else
		{
			update(lson, L, mid);
			update(rson, mid + 1, R);
		}
	p -> sum += R - L + 1;
}
int query(node_inside *&p, int l, int r, int L, int R)
{
	if (p == NULL) return 0;
	if (L == l && r == R) return query(p);
	int res = (R - L + 1) * query(p, 0);
	if (R <= mid) return query(lson, L, R) + res;
	else if (L >  mid) return query(rson, L, R) + res;
	else return query(lson, L, mid) + query(rson, mid + 1, R) + res;
}
struct node_outside
{
	node_inside *rt;
	node_outside *ls, *rs;
	node_outside() : ls(NULL), rs(NULL), rt(NULL){}
};

node_outside *T;
void update(node_outside *&p, int l, int r, int L, int R, int pos)
{
	if (p == NULL) p = new node_outside();
	update(p -> rt, 1, n, L, R);
	if (l == r) return;
	if (pos <= mid) update(lson, L, R, pos);
	else update(rson, L, R, pos);
}
int query(node_outside *&p, int l, int r, int L, int R, int pos)
{
	if (l == r) return l;
	int cnt = p -> rs == NULL ? 0 : query(p -> rs -> rt, 1, n, L, R);
	if (cnt >= pos) return query(rson, L, R, pos);
	else return query(lson, L, R, pos - cnt);
}

int main()
{
#ifdef CraZYali
	freopen("3110.in", "r", stdin);
	freopen("3110.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		int opt(read<int>()), a(read<int>()), b(read<int>()), c(read<int>());
		if (opt == 1) update(T, 1, n, a, b, c);
		else printf("%d\n", query(T, 1, n, a, b, c));
	}
	return 0;
}
