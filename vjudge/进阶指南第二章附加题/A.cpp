#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxN = 10000 + 5, maxlen = 55, sumS = maxN * maxlen, maxn = 1e6 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int n;
char s[maxN][maxlen], T[maxn];

int ch[sumS][26], rt, cur, cnt[sumS], fail[sumS];

void clear()
{
	REP(i, 0, cur)
		REP(j, 0, 25) ch[i][j] = 0;
	REP(i, 0, cur) cnt[i] = 0;
	rt = cur = 0;
}

bool insert(char s[])
{
	int len = strlen(s + 1);
	int now = rt;
	REP(i, 1, len)
	{
		if (!ch[now][s[i]-'a']) ch[now][s[i]-'a'] = ++cur;
		now = ch[now][s[i]-'a'];
	}
	cnt[now]++;
}

int q[sumS], head, tail;
void build()
{
	head = 1;tail = 0;
	REP(i, 0, 25)
		if (ch[rt][i])
			fail[q[++tail] = ch[rt][i]] = rt;
	while (head <= tail)
	{
		int x = q[head++];
		REP(i, 0, 25)
			if (ch[x][i]) fail[q[++tail] = ch[x][i]] = ch[fail[x]][i];
			else ch[x][i] = ch[fail[x]][i];
	}
}

int query(char s[])
{
	int len = strlen(s + 1);
	int now = rt, ans = 0;
	REP(i, 1, len)
	{
		now = ch[now][s[i]-'a'];
		for (int x = now; x && ~cnt[x] ; x = fail[x]) ans += cnt[x], cnt[x] = -1;
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	int Case = read<int>();
	while (Case --> 0)
	{
		n = read<int>();
		clear();
		REP(i, 1, n)
		{
			scanf("%s", s[i] + 1);
			insert(s[i]);
		}
		build();
		scanf("%s", T + 1);
		printf("%d\n", query(T));
	}
	return 0;
}
