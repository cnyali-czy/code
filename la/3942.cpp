#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
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
const int maxlen = 300000 + 10, MOD = 20071027;

int m, n, k;

struct node
{
	char c;
	bool com;
	node *ch[30];
	node()
	{
		c = '\0';
		com = 0;
		REP(i, 0, 26) ch[i] = NULL;
	}
	node(char _c) : c(_c)
	{
		com = 0;
		REP(i, 0, 26) ch[i] = NULL;
	}
};

vector <char> v;

int dp[maxlen];

struct Trie
{
	node *root;
	Trie() {root = new node;}
	void dfs(node *now)
	{
		REP(i, 0, 25)
			if (now -> ch[i] != NULL) dfs(now -> ch[i]);
		delete(now);
	}
	void init()	{dfs(root);root = new node;}
	void insert(char s[])
	{
		int len = strlen(s + 1);
		node *now = root;
		REP(i, 1, len)
		{
			if (now -> ch[s[i] - 'a'] == NULL) now -> ch[s[i] - 'a'] = new node(s[i]);
			now = now -> ch[s[i] - 'a'];
		}
		now -> com = 1;
	}
	void calc(char s[])
	{
		int len = strlen(s + 1);

		REP(i, 1, len) dp[i] = 0;
		dp[len + 1] = 1;
		DREP(i, len, 1)
		{
			node *now = root;
			REP(j, i, len)
				if (now -> ch[s[j] - 'a'] == NULL) break;
				else
				{
					now = now -> ch[s[j] - 'a'];
					dp[i] = (dp[i] + (now -> com) * dp[j + 1]) % MOD;
				}
		}
	}
}T;

char s[maxlen], t[maxlen];

int main()
{
#ifdef CraZYali
	freopen("3942.in", "r", stdin);
	freopen("3942.out", "w", stdout);
#endif
	register int Case = 0;
	while (scanf("%s\n%d", s + 1, &m) != EOF)
	{
		T.init();

		while (m --> 0)
		{
			scanf("%s\n", t + 1);
			T.insert(t);
		}
		T.calc(s);
		printf("Case %d: %d\n", ++Case, (dp[1] + MOD) % MOD);
	}
	
	return 0;
}
