#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
const int maxn = 30000 + 10;

template <typename T> inline T read()
{
	register T ans(0), p(1);
	register char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = (ans << 1) + (ans << 3)  + (c ^ 48);
		c = getchar();
	}
	return ans * p;
}

int m, n, k;

struct node
{
	int hp, ord;
	node(int VAL, int ORD) {hp = VAL;ord = ORD;}
	bool operator < (node B) const {return hp < B.hp || hp == B.hp && ord < B.ord;}
};

tree <node, null_type, less<node>, rb_tree_tag, tree_order_statistics_node_update> T;
tree <node, null_type, less<node>, rb_tree_tag, tree_order_statistics_node_update> :: iterator it;
tree <int, int> app;
int A[maxn];

int main()
{
	freopen("war.in", "r", stdin);
	freopen("war.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n)
	{
		app[A[i] = read<int>()]++;
		T.insert(node(A[i], i));
	}

	m = read<int>();
	while (m--)
	{
		register char c = getchar();
		while (c ^ 'C' && c ^ 'A' && c ^ 'Q') c = getchar();
		if (c == 'Q')
		{
			k = read<int>();
			if (n < k) printf("-1\n");
			else printf("%d\n", T.find_by_order(n - k) -> hp);
		}
		else
		{
			int i(read<int>()), a(read<int>());
			app[A[i]]--;
			T.erase(T.find(node(A[i], i)));
			if (c == 'A')
			{
				A[i] -= a;
				if (A[i] > 0)
				{
					T.insert(node(A[i], i));
					app[A[i]]++;
				}
				else n--;
			}
			else
			{
				app[A[i] += a]++;
				T.insert(node(A[i], i));
			}
		}
	}
	printf("%d", n);
	return 0;
}
