#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> inline T read()
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

struct node *null;
struct node
{
	node *ls, *rs;
	int val, dis, id;
	node(){}
	node(int _val, int _id) : val(_val), id(_id), dis(0), ls(null), rs(null) {}
};
int dis(node *p) {return p -> dis;}

int n, m;

struct Heap
{
	node *rt;
	Heap() : rt(null) {}
	node* merge(node* A, node *B)
	{
		if (A == null) return B;
		else if (B == null) return A;
		else
		{
			if (A -> val > B -> val || A -> val == B -> val && A -> id > B -> id) swap(A, B);
			A -> rs = merge(A -> rs, B);
			if (dis(A -> ls) < dis(A -> rs)) swap(A -> ls, A -> rs);
			A -> dis = dis(A -> rs) + 1;
			return A;
		}
	}
	void insert(int val, int id)
	{
		node *p = new node(val, id);
		if (rt == null || rt == NULL) rt = p;
		else rt = merge(rt, p);
	}
	pair <int, int> top() {return make_pair(rt -> val, rt -> id);}
	void pop() {rt = merge(rt -> ls, rt -> rs);}
	Heap operator + (Heap B) {Heap res = *this;res.rt = merge(res.rt, B.rt);return res;}
	Heap operator +=(Heap B) {return *this = *this + B;}
}H[maxn];

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

bool del[maxn];
void uni(int x, int y)
{
	if (del[x] + del[y]) return;
	x = find(x);y = find(y);
	if (x == y) return;
	H[fa[x] = y] += H[x];
}

int main()
{
#ifdef CraZYali
	freopen("3377-new-new.in", "r", stdin);
	freopen("3377-new-new.out", "w", stdout);
#endif
	null = new node();
	null -> ls = null -> rs = null;
	null -> dis = -1;
	cin >> n >> m;
	REP(i, 1, n) H[i].insert(read<int>(), fa[i] = i);
	while (m --> 0)
	{
		int opt(read<int>()), x(read<int>());
		if (opt == 1) uni(x, read<int>());
		else if (!del[x])
		{
			x = find(x);
			printf("%d\n", H[x].top().first);
			del[H[x].top().second] = 1;
			H[x].pop();
		}
		else puts("-1");
	}
	return 0;
}
