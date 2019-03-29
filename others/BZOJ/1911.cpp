#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
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

int n, a, b, c, s[maxn], dp[maxn];
int q[maxn], head, tail;

double K(int k, int j) {return ((dp[k] - dp[j]) * 1. / (s[k] - s[j]) - b) / a + s[k] + s[j];}

signed main()
{
#ifdef CraZYali
	freopen("1911.in", "r", stdin);
	freopen("1911.out", "w", stdout);
#endif
	cin >> n >> a >> b >> c;
	REP(i, 1, n)
	{
		s[i] = s[i-1] + read<int>();
		while (head < tail && K(q[head+1], q[head]) < 2 * s[i]) head++;
		int ret = s[i] - s[q[head]];
		dp[i] = dp[q[head]] + a * ret * ret + b * ret + c;
		while (head < tail && K(q[tail-1], i) < K(q[tail-1], q[tail])) tail--;
		q[++tail] = i;
	}
	cout << dp[n] << endl;
	return 0;
}
