#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar(); while (!isdigit(c))
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

struct Trie
{
	char s[maxn];
	int len;

	int end[maxn], fail[maxn], ch[maxn][26], rt, cur;

	Trie()
	{
		rt = cur = 1;
		memset(end, 0, sizeof(end));
		memset(fail, 0, sizeof(end));
		memset(ch, 0, sizeof(end));
	}
	void insert(int &now, int pos)
	{
		if (!now) now = ++cur;
		if (pos < len) insert(ch[now][s[pos+1] - 'a'], pos + 1);
		else end[now]++;
	}
	void insert()
	{
		scanf("%s", s + 1);
		len = strlen(s + 1);
		insert(ch[rt][s[1]-'a'], 1);
	}

	int q[maxn], head, tail;
	void build()
	{
		head = 1;tail = 0;
		REP(i, 0, 25)
			if (ch[1][i])
				fail[q[++tail] = ch[1][i]] = 1;
		while (head <= tail)
		{
			int x = q[head++];
			REP(i, 0, 25)
				if (ch[x][i]) fail[q[++tail] = ch[x][i]] = ch[fail[x]][i];
				else ch[x][i] = ch[fail[x]][i];
		}
	}
	int query()
	{
		int res = 0;
		scanf("%s", s + 1);
		len = strlen(s + 1);
		int now = rt;
		REP(i, 1, len)
		{
			now = ch[now][s[i]-'a'];
			for (int x = now; x && ~end[x]; x = fail[x]) res += end[x], end[x] = -1;
		}
		return res;
	}
}T;

int n;

int main()
{
#ifdef CraZYali
	freopen("3808.in", "r", stdin);
	freopen("3808.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) T.insert();
	T.build();
	cout << T.query() << endl;
#ifdef CraZYali
	REP(i,1,T.cur)printf("%d%c",T.fail[i],i==T.cur?'\n':' ');
#endif
	return 0;
}
