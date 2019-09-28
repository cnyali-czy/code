#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long

using namespace std;
const int maxn = 1e6 + 10, inf = 1e10;

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

int n, dp[maxn];

pair <int, int> P[maxn], t[maxn];
int s[maxn], top;
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first;}

int q[maxn], val[maxn];

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		int T(read<int>()), X(read<int>());
		P[i] = make_pair(T, X);
	}
	sort(P + 1, P + 1 + n, cmp);
	REP(i, 1, n)
	{
		while (top && P[i].second > P[s[top]].second) top--;
		s[++top] = i;
	}
	REP(i, 1, top) t[i] = P[s[i]];
	REP(i, 1, top) P[i] = t[i];
	n = top;
	int head(1), tail(0), las(0);
	memset(dp, 127, sizeof(dp));
	dp[0] = 0;
	REP(i, 1, n)
	{
		while (head <= tail && P[i].first >= dp[q[head]]) las = q[head++];
		if (las < i) chkmin(dp[i], P[i].first + 2 * P[las + 1].second);
		if (head <= tail) chkmin(dp[i], val[head]);
		int cur = dp[i] + 2 * P[i+1].second;
		while (head <= tail && cur <= val[tail]) tail--;
		q[++tail] = i;val[tail] = cur;
	}
	cout << dp[n] << endl;
	return 0;
}
