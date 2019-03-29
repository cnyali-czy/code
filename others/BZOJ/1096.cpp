#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
#define int long long
const int maxn = 1e6 + 10;

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

int n, x[maxn], p[maxn], c[maxn], dp[maxn], s1[maxn], s2[maxn];

int q[maxn], head, tail;
double K(int k, int j) {return (s2[j] - s2[k] + dp[j] - dp[k]) * 1. / (s1[j] - s1[k]);}

signed main()
{
#ifdef CraZYali
	freopen("1096.in", "r", stdin);
	freopen("1096.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) x[i] = read<int>(), p[i] = read<int>(), c[i] = read<int>();
	REP(i, 1, n) s1[i] = s1[i-1] + p[i], s2[i] = s2[i-1] + x[i] * p[i];
	REP(i, 1, n)
	{
		while (head < tail && K(q[head + 1], q[head]) < x[i]) head++;
		dp[i] = dp[q[head]] + c[i] + x[i] * (s1[i-1] - s1[q[head]]) - (s2[i-1] - s2[q[head]]);
		while (head < tail && K(q[tail - 1], i) < K(q[tail], q[tail - 1])) tail--;
		q[++tail] = i;
	}
	cout << dp[n] << endl;
	return 0;
}
