#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10;

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k;

struct node
{
	node *l, *r;
	int val, order;
	node() {}
	node(int _val) : val(_val) {order = rand();l = r = NULL;}
};

struct Treap
{
	node* root;
	Treap() {root = NULL;}
	void dfs(node *now)
	{
		if (now == NULL) return;
		dfs(now -> l);
		printf("%d ", now -> val);
		dfs(now -> r);
	}
	void output() {dfs(root);}
	void left_rotate(node*& x)
	{
		node* y = x -> r;
		x -> r = y -> l;
		y -> l = x;
		x = y;
		if (root == x) root = y;
	}
	void right_rotate(node*& x)
	{
		node* y = x -> l;
		x -> l = y -> r;
		y -> r = x;
		x = y;
		if (root == x) root = y;
	}
	void insert(int val, node*& now)
	{
		if (now == NULL) now = new node(val);
		else
			if (val >= now -> val)
			{
				insert(val, now -> r);
				if (now -> r -> order > now -> order) left_rotate(now);
			}
			else
			{
				insert(val, now -> l);
				if (now -> l -> order > now -> order) right_rotate(now);
			}
	}
	void insert(int val) {insert(val, root);}
}T;

int main()
{
#ifdef CraZYali
	freopen("1177.in", "r", stdin);
	freopen("1177.out", "w", stdout);
#endif
	srand(time(0));
	cin >> n;
	REP(i, 1, n) T.insert(read<int>());
	T.output();	putchar(10);

	return 0;
}
