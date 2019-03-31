#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxN = 150 + 5, maxlen = 100, sumS = maxN * maxlen, maxn = 1e6 + 10;

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

int n, maxans;
char s[maxN][maxlen], T[maxn];

int ch[sumS][26], rt, cur, cnt[sumS], fail[sumS], Ans[sumS];

void clear()
{
	maxans = 0;
	memset(Ans, 0, sizeof(Ans));
	memset(ch, 0, sizeof(ch));
	memset(cnt, 0, sizeof(cnt));
	rt = cur = 0;
}

bool insert(char s[], bool mode)
{
	int len = strlen(s + 1);
	int now = rt;
	REP(i, 1, len)
	{
		if (!ch[now][s[i]-'a']) ch[now][s[i]-'a'] = ++cur;
		now = ch[now][s[i]-'a'];
	}
	if (!mode) cnt[now]++;
	else return Ans[now] == maxans;
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

bool query(char s[])
{
	int len = strlen(s + 1);
	int now = rt;
	REP(i, 1, len)
	{
		now = ch[now][s[i]-'a'];
		for (int x = now; x; x = fail[x])
		{
			Ans[x] += cnt[x];
			chkmax(maxans, Ans[x]);
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("3796.in", "r", stdin);
	freopen("3796.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF && n)
	{
		clear();
		REP(i, 1, n)
		{
			scanf("%s", s[i] + 1);
			insert(s[i], 0);
		}
		build();
		scanf("%s", T + 1);
		query(T);
		printf("%d\n", maxans);
		REP(i, 1, n)
			if (insert(s[i], 1)) puts(s[i] + 1);
	}
	return 0;
}
