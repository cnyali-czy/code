#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;
const int maxn = 1000000 + 10;

int h[maxn], v[maxn], tot[maxn];

int m, n, k, top;

stack <int> s;

inline void Push(int x)
{
	while (!s.empty() && h[s.top()] <= h[x]) s.pop();
	if (!s.empty()) tot[s.top()] += v[x];
	s.push(x);
}

int main()
{
#ifdef CraZYali
	LKAKIOI
	LKAKIOI
	LKAKIOI
	LKAKIOI
	LKAKIOI
	LKAKIOI
	LKAKIOI
	LKAKIOI
	freopen("1901.in", "r", stdin);
	freopen("1901.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d%d", h + i, v + i);
	REP(i, 1, n) Push(i);
	while (s.size()) s.pop();
	DREP(i, n, 1) Push(i);
	int ans = 0;
	REP(i, 1, n) chkmax(ans, tot[i]);
	cout << ans;
	return 0;
}
