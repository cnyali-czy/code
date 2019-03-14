#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;
const int maxn = 2500 + 10, maxm = 2500 + 10;

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

priority_queue <int, vector <int> , greater<int> > q;
pair <int, int> cow[maxn], bottle[maxm];

int n, m, cur, ans;

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) cow[i].first = read<int>(), cow[i].second = read<int>();
	REP(i, 1, m) bottle[i].first = read<int>(), bottle[i].second = read<int>();
	sort(cow + 1, cow + 1 + n);
	sort(bottle + 1, bottle + 1 + m);
	cur = 1;
	REP(i, 1, m)
	{
		while (cur <= n && cow[cur].first <= bottle[i].first) q.push(cow[cur++].second);
		while (!q.empty() && bottle[i].second)
		{
			int x = q.top();q.pop();
			if (x >= bottle[i].first)
			{
				ans++;
				bottle[i].second--;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
