#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 30000 + 10, inf = (((1 << 30) - 1) << 1) + 1;

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

int m, n, k, a[maxn];

struct node
{
	node *ls, *rs;
	int w;
	node(){ls = rs = NULL;w = 0;}
}*root;

inline void add(node *now, int pos, int w, int l, int r)
{
	now -> w += w;
	if (l == r) return;
	int mid = (l >> 1) + (r >> 1) + (l & 1 & r);
	if (mid >= pos)
	{
		if (now -> ls == NULL) now -> ls = new node;
		add(now -> ls, pos, w, l, r);
	}
	else
	{
		if (now -> rs == NULL) now -> rs = new node;
		add(now -> rs, pos, w, l, r);
	}
}

inline int kth(node* now, int pos, int l, int r)
{
	if (l == r) return l;
	int mid = (l >> 1) + (r >> 1) + (l & r & 1);
	if (now -> ls != NULL && now -> ls -> w >= pos)
		return kth(now -> ls, pos, l, mid);
	else
		return kth(now -> rs, pos, mid + 1, r);
}

int main()
{
	freopen("war.in", "r", stdin);
	freopen("war.out", "w", stdout);
	n = read<int>();
	root = new node;
	REP(i, 1, n) add(root, a[i] = read<int>(), 1, 1, inf);
	m = read<int>();
	while (m--)
	{
		register char c = getchar();
		while (c ^ 'A' && c ^ 'C' && c ^ 'Q') c = getchar();
		if (c == 'A')
		{
			int i(read<int>()), w(read<int>());
			add(root, a[i], -1, 1, inf);
			a[i] -= w;
			if (a[i] <= 0) n--;
			else add(root, a[i], 1, 1, inf);
		}
		else if (c == 'C')
		{
			int i(read<int>()), w(read<int>());
			add(root, a[i], -1, 1, inf);
			add(root, a[i] += w, 1, 1, inf);
		}
		else
		{
			k = read<int>();
			if (n >= k) printf("%d\n", kth(root, n - k + 1, 1, inf));
			else printf("-1\n");
		}
	}
	cout << n;
	return 0;
}
