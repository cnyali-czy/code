#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxlen = 1e6 + 10;

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
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

struct node
{
	node *ch[26];
	char c;
	int times;
	node() {REP(i, 0, 25) ch[i] = NULL;times = 0;}
	node(char _c, bool _times = 0) : c(_c) , times(_times){REP(i, 0, 25) ch[i] = NULL;times = 0;}
};

struct Trie
{
	node* root;

	char v[maxlen], N;

	void dfs(node *now)
	{
		if (now == NULL) return;
		if (now != root) v[++N] = now -> c;
		if (now -> times) {REP(i, 1, N) putchar(v[i]);putchar(10);}
		REP(i, 0, 25) dfs(now -> ch[i]);
		if (now != root) --N;
	}

	Trie() {root = new node;N = 0;}
	
	void insert(char s[])
	{
		register int len = strlen(s + 1);
		register node *now = root;
		REP(i, 1, len)
		{
			if (now -> ch[s[i] - 'a'] == NULL) now -> ch[s[i] - 'a'] = new node(s[i]);
			now = now -> ch[s[i] - 'a'];
		}
		now -> times++;
	}

	int query(char s[])
	{
		register int len = strlen(s + 1), ans = 0;
		register node *now = root;
		
		REP(i, 1, len)
		{
			if (now -> ch[s[i] - 'a'] == NULL) return ans;
			now = now -> ch[s[i] - 'a'];
			ans += now -> times;
		}
		return ans;
	}
}T;

char s[maxlen];

int main()
{
#ifdef CraZYali
	freopen("1601.in", "r", stdin);
	freopen("1601.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		scanf("%s", s + 1);
		T.insert(s);
	}
	while (m --> 0)
	{
		scanf("%s", s + 1);
		printf("%d\n", T.query(s));
	}
	return 0;
}
