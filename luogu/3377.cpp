#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100000 + 10, maxm = 100000 + 10;

int m, n, k;

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

struct node
{
	node *l, *r;
	int val, dis;
	node() {dis = 0;l = r = NULL;}
};

node *root[maxn];

void init(int val, int id)
{
	root[id] = new node;
	root[id] -> val = val;
}

inline int dis(node *x) {return x != NULL ? x -> dis : -1;}

node *merge(node *A, node *B)
{
	if (A == NULL) return B;
	else if (B == NULL) return A;
	else
	{
		if (B -> val > A -> val) swap(A, B);
		A -> r = merge(A -> r, B);
		if (dis(A -> l) < dis(A -> r)) swap(A -> l, A -> r);
		A -> dis = dis(A -> r) + 1;
		return A;
	}
}

int top(int x) {return root[x] -> val;}

void pop(int x) {root[x] = merge(root[x] -> l, root[x] -> r);}

int main()
{
#ifdef CraZYali
	freopen("3377.in", "r", stdin);
	freopen("3377.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		scanf("%d", &k);
		init(-k, fa[i] = i);
	}
	while (m --> 0)
	{
		register int opt, x, y;
		scanf("%d%d", &opt, &x);
		if (opt == 1)
		{
			scanf("%d", &y);
			x = find(x) ; y = find(y);
			root[y] = merge(root[y], root[x]);
			fa[x] = y;
		}
		else if (opt == 2)
			if (root[find(x)] != NULL)
			{
				printf("%d\n", -top(find(x)));
				pop(find(x));
			}
			else printf("-1\n");
	}
	return 0;
}
