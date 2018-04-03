#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 200 + 5;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

pair <int, int> a[maxn];

bool Q[maxn];
int time1, time2, t1, t2;

inline bool cmp(pair<int, int> A, pair<int, int> B) {return A.second > B.second;}

int main()
{
#ifdef CraZYali
	freopen("2577.in", "r", stdin);
	freopen("2577.out", "w", stdout);
	freopen("2577.err", "w", stderr);
#endif
	n = read<int>();
	REP(i, 1, n)
		a[i] = make_pair(read<int>(), read<int>());
	REP(i, 1, n + 20) Q[i] = i & 1;
	sort(a + 1, a + 1 + n, cmp);
	srand(n);
	int ans = 1e9, times = 3e4;
	while (times --> 0)
	{
		random_shuffle(Q + 1, Q + n + 21);
		t1 = t2 = time1 = time2 = 0;
		REP(i, 1, n)
			if (Q[i])
			{
				time1 += a[i].first;
				chkmax(t1, time1 + a[i].second);
			}
			else
			{
				time2 += a[i].first;
				chkmax(t2, time2 + a[i].second);
			}
		chkmin(ans, max(t1, t2));
	}
	cout << ans << endl;
	return 0;
}
