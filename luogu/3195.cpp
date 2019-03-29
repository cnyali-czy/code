#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
#define int long long
const int maxn = 50000 + 10, inf = 2e9;

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


int n, L;
int a[maxn], sum[maxn], s[maxn], dp[maxn];

int q[maxn], head, tail;

double K(int i, int j) {return (dp[i]-dp[j])/(s[i]-s[j])+s[i]+s[j];} // i > j

signed main()
{
#ifdef CraZYali
	freopen("3195.in", "r", stdin);
	freopen("3195.out", "w", stdout);
#endif
	cin >> n >> L;L++;	
	REP(i, 1, n) s[i] = i + (sum[i] = sum[i-1] + (a[i] = read<int>()));
	q[head = tail = 1] = 0;
	REP(i, 1, n)
	{
		dp[i] = inf;
		while (head < tail && K(q[head + 1], q[head]) < 2 * s[i] - 2 * L) head++;
		dp[i] = dp[q[head]] + (s[i] - s[q[head]] - L) * (s[i] - s[q[head]] - L);
		while (head < tail && K(i, q[tail - 1]) < K(q[tail - 1], q[tail])) tail--;
		q[++tail] = i;
	}
	cout << dp[n] << endl;
	return 0;
}
