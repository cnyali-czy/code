#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 50000 + 10;

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

int n, L;
int Sum[maxn], dp[maxn], f[maxn];

double cmp(int j, int k) {return (dp[k] - dp[j] + (f[k] - f[j]) * (f[j] + f[k] + L + L)) / (2. * (f[k] - f[j]));}
int head, tail, q[maxn];

signed main()
{
#ifdef CraZYali
	freopen("1010.in", "r", stdin);
	freopen("1010.out", "w", stdout);
#endif
	cin >> n >> L;++L;
	REP(i, 1, n) f[i] = i + (Sum[i] = Sum[i-1] + read<int>());
	//	dp[i] = min(dp[j] + (f[i] - f[j] - L) ^ 2)
	//	f[i] > f[j] (j < i)

	head = tail = 1;

	REP(i, 1, n)
	{
		while (head < tail && cmp(q[head], q[head + 1]) <= f[i]) head++;
		int x = q[head];
		dp[i] = dp[x] + (f[i] - f[x] - L) * (f[i] - f[x] - L);
		while (head < tail && cmp(q[tail], i) < cmp(q[tail-1], q[tail])) tail--;
		q[++tail] = i;
	}
	cout << dp[n] << endl;
	return 0;
}
