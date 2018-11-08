#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;

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

struct node
{
	int val, id, dis;
	node *l, *r;
	node() {l = r = NULL;dis = 0;}
	node(int _val, int _id, int _dis = 0) : dis(_dis), id(_id), val(_val) {l = r = NULL;}
};
int dis(node *A) {return A == NULL ? -1 : A -> dis;}

struct Heap
{
	node *root;
	Heap() {root = NULL;}
	void init(int val, int id) {root = new node(val, id);}
	node* merge(node *A, node *B)
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
	pair <int, int> top() {return make_pair(root -> val, root -> id);}
	void pop() {root = merge(root -> l, root -> r);}
	Heap operator + (Heap B) {Heap res = *this;res.root = merge(res.root, B.root);return res;}
	Heap operator += (Heap B) {return *this = *this + B;}
}H[maxn];
int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

bool del[maxn];
void uni(int x, int y)
{
	if (del[x] || del[y]) return;
	x = find(x);y = find(y);
	if (x ^ y)
	{
		fa[x] = y;
		H[y] += H[x];
	}
}
int n, m;

int main()
{
#ifdef CraZYali
	freopen("3377-new.in", "r", stdin);
	freopen("3377-new.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) H[i].init(read<int>(), fa[i] = i);
	while (m --> 0)
	{
		register int opt = read<int>(), x = read<int>();
		if (opt == 1 ) 
		{
			register int y = read<int>();
			uni(x, y);
		}
		else if (!del[x])
		{
			printf("%d\n", H[find(x)].top().first);
			del[H[find(x)].top().second] = 1;
			H[find(x)].pop();
		}
		else printf("-1\n");
	}
	return 0;
}
