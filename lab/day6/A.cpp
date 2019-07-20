#define REP(i, s, e) for (int i = s; i <= e ;i++)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1e6 + 10, inf = 1ll << 60ll;
const double eps = 1e-8;

int n, a[maxn], dp[maxn];
int f(int i, int j) {return dp[j] + a[i] - (i-j) * (i-j-1) / 2;}
namespace violence
{
	void work()
	{
		REP(i, 1, n+1)
		{
			dp[i] = a[i] - i * (i-1) / 2;
			REP(j, 1, i - 1) if (i == n+1 || a[j] <= a[i]) chkmax(dp[i], f(i, j));
		}
		cout << dp[n+1] << endl;
	}
}
namespace flag
{
	bool judge()
	{
		REP(i, 2, n) if (a[i] < a[i-1]) return 0;
		return 1;
	}
	int q[maxn], head, tail;
	double K(int k, int j) // j > k
	{
		return (dp[j] - dp[k]) * 1. / (k-j) + (k + j + 1.) * 1./ 2;
	}
	void work()
	{
		REP(i, 1, n)
		{
			dp[i] = a[i] - i * (i-1) / 2;
			while (head < tail && K(q[head], q[head+1]) - eps < i) head++;
			if (i > 1) dp[i] = f(i, q[head]);
			while (head < tail && K(q[tail-1], i) - eps < K(q[tail], q[tail-1])) tail--;
			q[++tail] = i;
		}
		dp[n+1] = -(n+1) * n / 2;
		REP(i, 1, n) chkmax(dp[n+1], f(n+1, i));
		cout << dp[n+1] << endl;
	}
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%lld", a + i);
	if (n <= 5000) violence::work();
	else flag::work();
	return 0;
}
