#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
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

int m, n, k;

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

bool del[maxn];

struct node
{
	node *l, *r;
	int val, id, dis;
	node() {dis = 0;l = r = NULL;}
};

int dis(node *x) {return x != NULL ? x -> dis : -1;}

struct Heap
{
	node *root;
	void init(int val, int id)
	{
		root = new node;
		root -> val = val;
		root -> id = id;
	}
	pair <int, int> top() {return make_pair(root -> val, root -> id);}
	node * merge(node * A, node * B)
	{
		if (A == NULL) return B;
		else if (B == NULL) return A;
		else
		{
			if (A -> val > B -> val || A -> val == B -> val && A -> id > B -> id) swap(A, B);
			A -> r = merge(A -> r, B);
			if (dis(A -> l) < dis(A -> r)) swap(A -> l, A -> r);
			A -> dis = dis(A -> r) + 1;
			return A;
		}
	}
	void merge(Heap B) {root = merge(root, B.root);}
	void pop() {root = merge(root -> l, root -> r);}
}H[maxn];

int main()
{
#ifdef CraZYali
	freopen("3377.in", "r", stdin);
	freopen("3377.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		fa[i] = i;
		H[i].init(read<int>(), i);
	}
	while (m --> 0)
	{
		register int opt(read<int>()), x(read<int>()), y;
		if (opt == 1)
		{
			y = read<int>();
			if (!del[x] && !del[y] && find(x) ^ find(y))
			{
				H[find(x)].merge(H[find(y)]);
				fa[find(y)] = find(x);
			}
		}
		else if (!del[x])
		{
			y = find(x);
			printf("%d\n", H[y].top().first);
			del[H[y].top().second] = 1;
			H[y].pop();
		}
		else printf("-1\n");
	}
	return 0;
}
