#define REP(i, s, e) for(register int i = s; i <= e ; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;
const int maxm = 100 + 5, maxn = 2000 + 10;

int n, m, k;
int a[maxn], b[maxn];

bool cmp(int a, int b) {return a > b;}

priority_queue <int> q;

void solve()
{
	REP(i, 1, n) q.push(a[i] + b[1]);
	REP(i, 1, n)
		REP(j, 2, n)
			if (a[i] + b[j] < q.top())
			{
				q.pop();
				q.push(a[i] + b[j]);
			}
	REP(i, 1, n)
	{
		a[n - i + 1] = q.top();
		q.pop();
	}
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	register int T;cin >> T;
	while (T --> 0)
	{
		scanf("%d%d", &m, &n);
		REP(i, 1, n) scanf("%d", a + i);
		sort(a + 1, a + 1 + n);
		REP(i, 2, m)
		{
			REP(j, 1, n) scanf("%d", b + j);
			solve();
		}
		REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ');
	}
	return 0;
}
