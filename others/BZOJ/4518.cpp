#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 3000 + 10, inf = 2e9;

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

int n, m, l[maxn], s[maxn], a[maxn];

int q[maxn], head, tail;
int dp[maxn][2];bool cur;
int A(int x) {return dp[x][cur ^ 1];}
double K(int j, int k) {return (A(j) - A(k)) * 1. / (s[j] - s[k]) + s[j] + s[k];}

signed main()
{
#ifdef CraZYali
	freopen("4518.in", "r", stdin);
	freopen("4518.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) s[i] = s[i-1] + (a[i] = read<int>());
	REP(i, 1, n) dp[i][cur ^ 1] = s[i] * s[i];
	REP(L, 2, m)
	{
		q[head = tail = 1] = 0;
		REP(i, 1, n)
		{
			while (head < tail && K(q[head + 1], q[head]) < 2 * s[i]) head++;
			dp[i][cur] = dp[q[head]][cur ^ 1] + (s[i] - s[q[head]]) * (s[i] - s[q[head]]);
			while (head < tail && K(i, q[tail - 1]) < K(q[tail-1], q[tail])) tail--;
			q[++tail] = i;
		}
		cur ^= 1;
	}
	cout << m * dp[n][cur ^ 1] - s[n] * s[n];
	return 0;
}
