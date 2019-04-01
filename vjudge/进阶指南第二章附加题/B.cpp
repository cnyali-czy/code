#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
const int maxN = 500 + 5, maxlen = 200 + 5, sumS = maxN * maxlen, maxn = 10000 + 10;

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

int n, m;
char s[maxN][maxlen], T[maxn];

int num[sumS], ch[sumS][130], rt, cur, cnt[sumS], fail[sumS];

bool insert(char s[], int id)
{
	int len = strlen(s + 1);
	int now = rt;
	REP(i, 1, len)
	{
		if (!ch[now][s[i]]) ch[now][s[i]] = ++cur;
		now = ch[now][s[i]];
	}
	num[now] = id;
	cnt[now]++;
}

int q[sumS], head, tail;
void build()
{
	head = 1;tail = 0;
	REP(i, 0, 129)
		if (ch[rt][i])
			fail[q[++tail] = ch[rt][i]] = rt;
	while (head <= tail)
	{
		int x = q[head++];
		REP(i, 0, 129)
			if (ch[x][i]) fail[q[++tail] = ch[x][i]] = ch[fail[x]][i];
			else ch[x][i] = ch[fail[x]][i];
	}
}
bool vis[sumS];
int ans[maxN];
void query(char s[])
{
	int len(strlen(s + 1)), now(rt);
	REP(i, 1, len)
	{
		now = ch[now][s[i]];
		for (int x = now; x && !vis[x] ; x = fail[x])
		{
			vis[x] = 1;
			if (cnt[x]) ans[++ans[0]] = num[x];
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%s", s[i] + 1);
		int len = strlen(s[i] + 1);
		insert(s[i], i);
	}
	build();
	m = read<int>();
	int total = 0;
	REP(i, 1, m)
	{
		memset(vis, 0, sizeof(vis));
		scanf("%s", T + 1);
		int len = strlen(T + 1);
		ans[0] = 0;
		query(T);
		if (ans[0] > 0)
		{
			sort(ans + 1, ans + 1 + ans[0]);
			ans[0] = unique(ans + 1, ans + 1 + ans[0]) - ans - 1;
			printf("web %d: ", i);
			REP(i, 1, ans[0]) printf("%d%c", ans[i], i == ans[0] ? '\n' : ' ');
			total++;
		}
	}
	printf("total: %d\n", total);
	return 0;
}
