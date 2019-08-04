#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 20, maxnode = maxn << 1;

long long n, u, v, dp[maxn];
char s[maxn];

const int siz = 26;
int Max[maxnode], ch[maxnode][siz], ne[maxnode], start, last, cur;
inline void clear()
{
	REP(i, 1, cur)
	{
		ne[i] = Max[i] = 0;
		REP(j, 0, siz - 1) ch[i][j] = 0;
	}
	cur = 0;
}
inline int newnode(int _Max = 0)
{
	return Max[++cur] = _Max, cur;
}
inline void init()
{
	start = last = newnode();
}
inline void extend(int c)
{
	int u = newnode(Max[last] + 1), v = last;
	for (;v && !ch[v][c];v = ne[v]) ch[v][c] = u;
	if (!v) ne[u] = start;
	else if (Max[v] + 1 == Max[ch[v][c]]) ne[u] = ch[v][c];
	else
	{
		int New(newnode(Max[v] + 1)), Old(ch[v][c]);
		REP(i, 0, siz - 1) ch[New][i] = ch[Old][i];
		ne[New] = ne[Old];
		ne[u] = ne[Old] = New;
		for (; v && ch[v][c] == Old;v = ne[v]) ch[v][c] = New;
	}
	last = u;
}
#define Min(u) (Max[ne[u]] + 1)

int main()
{
#ifdef CraZYali
	freopen("6583.in", "r", stdin);
	freopen("6583.out", "w", stdout);
#endif
	while (scanf("%s%lld%lld", s + 1, &u, &v) != EOF)
	{
		n = strlen(s + 1);
		clear();
		init();
		int p = start, l = 1;
		REP(r, 1, n)
		{
			dp[r] = dp[r-1] + u;
			int c = s[r] - 'a';
			while ((r - l + 1 > l - 1 || !ch[p][c]) && l <= r)
			{
				extend(s[l++] - 'a');
				while (p && Min(p) >= r - l + 1) p = ne[p];
				if (!p) p = 1;
			}
			p = ch[p][c];
			while (p && Min(p) > r - l + 1) p = ne[p];
			if (!p) p = 1;
			if (l <= r) chkmin(dp[r], dp[l-1] + v);
		}
		printf("%lld\n", dp[n]);
	}	
	return 0;
}
