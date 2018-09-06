#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10, maxlen = 200 + 5;

int m, n, k;

struct node
{
	node* ch[2];
	long long cnt;
	node(){ch[0] = ch[1] = NULL;cnt = 0;}
};

struct Trie
{
	node *root;
	Trie() {root = new node;}

	void del_dfs(node *now)
	{
		if (now -> ch[0] != NULL) del_dfs(now -> ch[0]);
		if (now -> ch[1] != NULL) del_dfs(now -> ch[1]);
		now -> ch[0] = now -> ch[1] = NULL;
		delete(now);
		now = NULL;
	}

	void clear() {del_dfs(root);root = new node;}
	
	void insert(bool t[], int len)
	{
		node *now = root;
		REP(i, 1, len)
		{
			if (now -> ch[t[i]] == NULL) now -> ch[t[i]] = new node;
			now = now -> ch[t[i]];
			now -> cnt++;
		}
	}

	long long dfs(node *now, long long depth)
	{
		if (now == NULL) return 0;
		register long long ret = now -> cnt * depth;
		chkmax(ret, dfs(now -> ch[0], depth + 1));
		chkmax(ret, dfs(now -> ch[1], depth + 1));
		return ret;
	}
}T;

char s[maxlen];
bool t[maxlen];

int main()
{
#ifdef CraZYali
	freopen("11488.in", "r", stdin);
	freopen("11488.out", "w", stdout);
#endif
	register int Case;
	cin >> Case;
	while (Case --> 0)
	{
		T.clear();
		scanf("%d\n", &n);
		REP(i, 1, n)
		{
			scanf("%s", s + 1);
			register int len = strlen(s + 1);
			REP(i, 1, len) t[i] = s[i] - '0';
			T.insert(t, len);
		}
		printf("%lld\n", T.dfs(T.root, 0));
	}
	
	return 0;
}
