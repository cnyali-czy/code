#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%d] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 100010;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;
char s[205];

struct Trie
{
	struct node
	{
		node *ne[2];
		bool is;char x;
		node() {ne[0] = ne[1] = NULL;x = '\0';is = 0;}
	}*root;
	inline void init() {root = new node;}
	inline void insert(char s[], int len, node* now , int pos = 1)
	{
		if (pos == len)
		{
			now -> is = 1;
			return;
		}
		if (now -> ne[s[pos]]) insert(s, len, now -> ne[s[pos]], pos + 1);
		else
		{
			now -> ne[s[pos]] = new node;
			now -> x = s[pos + 1];
			insert(s, len, now -> ne[s[pos]], pos + 1);
		}
	}
};

int main()
{
#ifdef CraZYali
	freopen("11488.in", "r", stdin);
	freopen("11488.out", "w", stdout);
#endif
	int T = read<int>();
	while (T--)
	{
		Trie t;t.init();
		n = read<int>();
		REP(i, 1, n)
		{
			scanf("%s", s + 1);
			int len = strlen(s + 1);
			REP(j, 1, len) s[j] -= '0';
			t.insert(s, len, t.root);
		}
	}

	return 0;
}
