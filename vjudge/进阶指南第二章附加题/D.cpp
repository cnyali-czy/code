#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxN = 55, maxlen = 20 + 5, sumS = maxN * maxlen, maxn = 1000 + 10, inf = 0x3f3f3f3f;

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
char s[maxn];

int to(char c)
{
	return (c == 'C') + (c == 'G') * 2 + (c == 'T') * 3;
}

int ch[sumS][4], rt, cur, fail[sumS];
bool End[sumS];
void clear()
{
	REP(i, 0, cur)
	{
		End[i] = fail[i] = 0;
		REP(j, 0, 3)
			ch[i][j] = 0;
	}
	rt = cur = 0;
}

void insert(char s[])
{
	int len(strlen(s + 1)), now(rt);
	REP(i, 1, len)
	{
		s[i] = to(s[i]);
		if (!ch[now][s[i]]) ch[now][s[i]] = ++cur;
		now = ch[now][s[i]];
	}
	End[now] = 1;
}
int q[sumS], head, tail;
void build()
{
	head = 1;tail = 0;
	REP(i, 0, 3)
		if (ch[0][i]) q[++tail] = ch[0][i];
	while (head <= tail)
	{
		int x = q[head++];
		if (End[fail[x]]) End[x] = 1;
		REP(i, 0, 3)
			if (ch[x][i]) fail[q[++tail] = ch[x][i]] = ch[fail[x]][i];
			else ch[x][i] = ch[fail[x]][i];
	}
}
int dp[maxn][sumS];
int solve(char s[])
{
	int len = strlen(s + 1);
	REP(i, 1, len)
	{
		s[i] = to(s[i]);
		memset(dp[i], inf, sizeof(dp[i]));
		REP(j, 0, cur)
			REP(k, 0, 3)
			if (!End[ch[j][k]]) chkmin(dp[i][ch[j][k]], dp[i-1][j] + (s[i] != k));
	}	
	int ans = inf;
	REP(i, 0, cur) chkmin(ans, dp[len][i]);
	return ans == inf ? -1 : ans;
}
int Case;

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	int n;
	while (n = read<int>())
	{
		clear();
		REP(i, 1, n)
		{
			scanf("%s", s + 1);
			insert(s);
		}
		build();
		scanf("%s", s + 1);
		printf("Case %d: %d\n", ++Case, solve(s));
	}
	return 0;
}
