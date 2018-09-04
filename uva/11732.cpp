#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxlen = 1000 + 5;

int m, n, k;

int idofc(char c)
{
	if (isdigit(c)) return c - '0';
	else if ('A' <= c && c <= 'Z') return c - 'A' + 10;
	else return c - 'a' + 1 + idofc('Z');
}

const int Max = 62;

struct node
{
	node *ch[Max];
	bool is;
	int siz;
	node() {siz = is = 0;REP(i, 0, 61) ch[i] = NULL;}
};

struct Trie
{
	node *root;
	void dfs_del(node *now)
	{
		if (now == NULL) return;
		REP(i, 0, 61) dfs_del(now -> ch[i]);
		REP(i, 0, 61) now -> ch[i] = NULL;
		delete(now);
	}
	void clear()
	{
		dfs_del(root);
		root = new node;
	}

	void insert(char s[])
	{
		register int len = strlen(s + 1);
		root -> siz++;
		node *now = root;
		REP(i, 1, len)
		{
			if (now -> ch[idofc(s[i])] == NULL) now -> ch[idofc(s[i])] = new node;
			now = now -> ch[idofc(s[i])];
			now -> siz++;
		}
		now -> is = 1;
	}
	
	long long ans;

	void dfs(node *now, int depth)
	{
		bool flag = 1;
		REP(i, 0, 61) if (now -> ch[i] != NULL) {flag = 0;break;}
		if (flag) ans += (long long)now -> siz * (now -> siz - 1) * depth;
		else
		{
			register long long ret = 0;
			REP(i, 0, 61)
				if (now -> ch[i] != NULL) ret += (long long)now -> ch[i] -> siz * (now -> siz - now -> ch[i] -> siz);
			ans += (long long)ret / 2 * (2 * depth + 1);
			REP(i, 0, 61)
				if (now -> ch[i] != NULL) dfs(now -> ch[i], depth + 1);
		}
	}

	long long calc()
	{
		ans = 0;
		dfs(root, 0);
		return ans;
	}
}T;

char s[maxlen];

int main()
{
#ifdef CraZYali
	freopen("11732.in", "r", stdin);
	freopen("11732.out", "w", stdout);
#endif
	register int Case(0);
	while (scanf("%d\n", &n) * n)
	{
		T.clear();
		while (n--)
		{
			scanf("%s", s + 1);
			T.insert(s);
		}
		printf("Case %d: %lld\n", ++Case, T.calc());
	}
	return 0;
}
