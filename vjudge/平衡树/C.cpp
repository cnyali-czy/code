#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)
#define DEBUG
//#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
const int maxn = 100000+100000 + 10, inf = 1e9;

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

struct node
{
	int l, r, s, val, mn, tag_rotate, tag_lazy, order;
	node(){}
	node(int _val) : l(0), r(0), s(1), val(_val), mn(_val), tag_rotate(0), tag_lazy(0), order(rand()){}
}t[maxn];
int root, cnt;
void rev(int x)
{
	t[x].tag_rotate ^= 1;
	swap(t[x].l, t[x].r);
}
int newnode(int val)
{
	t[++cnt] = node(val);
	return cnt;
}
void maintain(int x)
{
	if (!x) return;
	t[x].s = t[t[x].l].s + t[t[x].r].s + 1;
	t[x].mn = min(t[x].val, min(t[t[x].l].mn, t[t[x].r].mn));
}
void pushdown(int x)
{
	if (!x) return;
	int l = t[x].l,&r = t[x].r;
	if (t[x].tag_lazy)
	{
		if (l)
		{
			t[l].tag_lazy += t[x].tag_lazy;
			t[l].val += t[x].tag_lazy;
			t[l].mn += t[x].tag_lazy;
		}
		if(r)
		{
			t[r].tag_lazy += t[x].tag_lazy;
			t[r].val += t[x].tag_lazy;
			t[r].mn += t[x].tag_lazy;
		}
		t[x].tag_lazy = 0;
	}
	if (t[x].tag_rotate)
	{
		t[x].tag_rotate = 0;
		rev(l);
		rev(r);
	}
}
void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
	{
		pushdown(x);
		if (t[t[x].l].s >= siz) split(t[b = x].l, a, t[x].l, siz);
		else split(t[a = x].r, t[x].r, b, siz - t[t[x].l].s - 1); 
		maintain(x);
	}
}
void merge(int &x, int a, int b)
{
	if (!(a * b)) x = a + b;
	else
	{
		if (t[a].order > t[b].order)
		{
			pushdown(b);
			merge(t[x = b].l, a, t[b].l);
		}
		else
		{
			pushdown(a);
			merge(t[x = a].r, t[a].r, b);
		}
		maintain(x);
	}
}
void add(int l, int r, int d)
{
	int x(0), y(0), z(0);
	split(root, x, y, l - 1);
	split(y, y, z, r - l + 1);
	t[y].tag_lazy += d;
	t[y].mn += d;
	t[y].val += d;
	merge(y, y, z);
	merge(root, x, y);
}
void reverse(int l, int r)
{
	int x(0), y(0), z(0);
	split(root, x, y, l - 1);
	split(y, y, z, r - l + 1);
	rev(y);
	merge(y, y, z);
	merge(root, x, y);
}
void revolve(int l, int r, int times)
{
	times %= (r - l + 1);
	int x(0), y(0), z(0), p(0);
	split(root, x, y, l - 1);
	split(y, y, z, r - l + 1);
	split(y, y, p, r - l + 1 - times);
	merge(y, p, y);
	merge(y, y, z);
	merge(root, x, y);
}
void insert(int pos, int val)
{
	int x(0), y(0), z(newnode(val));
	split(root, x, y, pos);
	merge(x, x, z);
	merge(root, x, y);
}
void del(int pos)
{
	int x(0), y(0), z(0);
	split(root, x, y, pos);
	split(x, x, z, pos-1);
	merge(root, x, y);
}
int Min(int l, int r)
{
	int x(0), y(0), z(0);
	split(root, x, y, l - 1);
	split(y, y, z, r - l + 1);
	int ans = t[y].mn;
	merge(y, y, z);
	merge(root, x, y);
	return ans;
}
void push_back(int val)
{
	int z(newnode(val));
	merge(root, root, z);
}

int n, m, k;
void output(int x = root)
{
	if(!x)return;
	pushdown(x);
	output(t[x].l);
	printf("%d ",t[x].val);
	output(t[x].r);
	/*
	REP(i, 1, n)
		REP(j, i, n)
		printf("%d %d %d\n", i, j, Min(i, j));
	puts("-------------");
	*/
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n;
	t[0].mn = t[0].val = inf;
	REP(i, 1, n) push_back(read<int>());
//	output();
	cin >> m;
	REP(i,1,m)
	{
		string s;
		cin >> s;
		if (s == "ADD")
		{
			int x(read<int>()), y(read<int>()), D(read<int>());
			DEBUG;
			add(x, y, D);
			DEBUG;
		}
		else if (s == "REVERSE")
		{
			int x(read<int>()), y(read<int>());
			DEBUG;
			reverse(x, y);
			DEBUG;
		}
		else if (s == "REVOLVE")
		{
			int x(read<int>()), y(read<int>()), T(read<int>());
			revolve(x, y, T);
		}
		else if (s == "INSERT")
		{
			int x(read<int>()), P(read<int>());
			insert(x, P);
		}
		else if (s == "DELETE")
		{
			DEBUG;
			del(read<int>());
			DEBUG;
		}
		else
		{
			int x(read<int>()), y(read<int>());
			DEBUG;
			printf("%d\n", Min(x, y));
			DEBUG;
		}
//		output();cout<<endl;
	}

	return 0;
}
