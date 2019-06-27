#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <set>
#define int long long

using namespace std;
const int maxn = 50000 + 10;

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
pair <int, int> e[maxn], E[maxn];

bool cmp1(pair <int, int> A, pair <int, int> B) {return A.first < B.first || A.first == B.first && A.second < B.second;}
bool cmp2(pair <int, int> A, pair <int, int> B) {return A.first < B.first || A.first == B.first && A.second > B.second;}
multiset <int> s;

int Max[maxn][18], LOG;
int query(int l, int r)
{
	int k = log2(r - l + 1);
	return max(Max[l][k], Max[r - (1 << k) + 1][k]);
}

int q[maxn], head, tail, dp[maxn];
int part1(int j, int k) {return dp[j] - dp[k];}
int part2(int j, int k, int i) {return query(k+1, i) - query(j + 1, i);}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n;
	REP(i, 1, n) scanf("%lld%lld", &e[i].first, &e[i].second);
	sort(e + 1, e + 1 + n, cmp1);
	REP(i, 1, n) s.insert(-e[i].second);
	REP(i, 1, n)
	{
		s.erase(s.find(-e[i].second));
		if (-(*s.begin()) < e[i].second) e[++m] = e[i];
	}
	n = m;
//	sort(e + 1, e + 1 + n, cmp1);
	LOG = log2(n);
	REP(i, 1, n) Max[i][0] = e[i].second;
	REP(i, 1, n)
		for (int j = 1; i + (1 << j) - 1 <= n; j++)
			Max[i][j] = max(Max[i][j-1], Max[i + (1 << j-1)][j-1]);
	REP(i, 1, n)
	{
		while (head < tail && part1(q[head+1], q[head]) < e[i].first * part2(q[head+1], q[head], i)) head++;
		dp[i] = dp[q[head]] + e[i].first * query(q[head] + 1, i);
		while (head < tail && part1(i, q[tail-1]) * part2(q[tail]-1, q[tail-1]-1, i) < part1(q[tail], q[tail-1]) * part2(i-1, q[tail-1]-1, i)) tail--;
		q[++tail] = i;
	}
	cout << dp[n] << endl;
	return 0;
}
