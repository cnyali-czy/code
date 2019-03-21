#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10, inf = 1e9;

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

int m;
int s1[maxn], s2[maxn], t1, t2;
int sum[maxn], dp[maxn];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	while (scanf("%d", &m) != EOF)
	{
		t1 = t2 = 0;
		dp[0] = -inf;
		while (m --> 0)
		{
			char c = getchar();
			while (c != 'I' && c != 'D' && c != 'L' && c != 'R' && c != 'Q') c = getchar();
			if (c == 'I')
			{
				++t1;
				dp[t1] = max(dp[t1-1], sum[t1] = sum[t1-1] + (s1[t1] = read<int>()));
			}
			else if (c == 'D') dp[t1--]=0;
			else if (c == 'L') {if (t1) s2[++t2] = s1[t1--];}
			else if (c == 'R') {if (t2) {s1[++t1] = s2[t2--];dp[t1] = max(dp[t1-1], sum[t1] = sum[t1-1] + s1[t1]);}}
			else printf("%d\n", dp[min(t1, read<int>())]);
		}
	}
	return 0;
}
