#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr. "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#define int long long

using namespace std;
const int maxn = 500000 + 10;

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n;

int a[maxn], s[maxn];
int dp[maxn], q[maxn], head, tail;

int part1(int j, int k) {return dp[j] - dp[k] + s[j] * s[j] - s[k] * s[k];}
int part2(int j, int k) {return s[j] - s[k];}
bool judge1(int j, int k, int i) {return part1(j, k) <= 2 * s[i] * part2(j, k);}
bool judge2(int a, int b, int c) {return part1(a, b) * part2(c, b) <= part1(c, b) * part2(a, b);}

long double K(int j, int k) {return (dp[j] - dp[k] + s[j] * s[j] - s[k] * s[k]) * 1. / (s[j] - s[k]);}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	while (scanf("%lld%lld", &n, &m) != EOF)
	{
		REP(i, 1, n)
		{
			scanf("%lld", a + i);
			s[i] = s[i-1] + a[i];
		}
		head = tail = 0;
		REP(i, 1, n)
		{
			while (head < tail && judge1(q[head+1], q[head], i)) head++;
			dp[i] = dp[q[head]] + (s[i] - s[q[head]]) * (s[i] - s[q[head]]) + m;
			while (head < tail && judge2(i, q[tail-1], q[tail])) tail--;
			q[++tail] = i;
		}
		printf("%lld\n", dp[n]);
	}
	return 0;
}
