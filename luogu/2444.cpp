#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 2000 + 10, maxlen = 30000 + 10, sumS = maxlen;

int ch[sumS][3], fail[sumS], rt, cur;
bool End[sumS];
void insert(char s[])
{
	int now = rt;
	for (int i = 1; s[i]; i++)
		now = !ch[now][s[i]] ? ch[now][s[i]] = ++cur : ch[now][s[i]];
	End[now] = 1;
}
int q[sumS], head, tail;
void build()
{
	head = 1;
	REP(i, 1, 2) if (ch[0][i]) q[++tail] = ch[0][i];
	while (head <= tail)
	{
		int x = q[head++];
		if (End[fail[x]]) End[x] = 1;
		REP(i, 1, 2)
			if (ch[x][i]) fail[q[++tail] = ch[x][i]] = ch[fail[x]][i];
			else ch[x][i] = ch[fail[x]][i];
	}
}

bool vis[sumS], ins[sumS];
void dfs(int x = rt)
{
	if (ins[x]) {puts("TAK");exit(0);}
	if (vis[x] || End[x]) return;
	vis[x] = ins[x] = 1;
	REP(i, 1, 2) if (ch[x][i]) dfs(ch[x][i]);
	ins[x] = 0;
}

int n;
char s[maxlen];

int main()
{
#ifdef CraZYali
	freopen("2444.in", "r", stdin);
	freopen("2444.out", "w", stdout);
#endif
	cin >> n;
	while (n--)
	{
		scanf("%s", s + 1);
		for (int i = 1; s[i]; i++) s[i] -= '0'-1;
		insert(s);
	}
	build();
#ifdef CraZYali
	REP(i, 1, cur) printf("%d%c", (int)fail[i], i == cur ? '\n' : ' ');
	REP(i, 1, cur) printf("%d%c", (int)End[i], i == cur ? '\n' : ' ');
#endif
	dfs();
	puts("NIE");
	return 0;
}
