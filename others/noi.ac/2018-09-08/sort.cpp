#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10;

int n, m, k;
int a[maxn];

namespace cheat
{
	void work()
	{
		REP(i, 1, n)
			REP(j, 1, n - i)
				if (a[j] > a[j + 1])
				{
					swap(a[j], a[j + 1]);
					printf("%d %d\n", j, j + 1);
				}
		printf("-1 -1");
	}
};

inline void rvs(int l, int r)
{
	if (l < r)
	{
		printf("%d %d\n", l, r);
		reverse(a + l, a + r + 1);
	}
}

int ret;

void work(int l, int r)
{
	if (l >= r) return;
	register int mid = l + r >> 1;
	work(l, mid);
	work(mid + 1, r);
	register int x(mid), y(mid + 1);
	while (x >= l && a[x] > ret) x--;
	while (y <= r && a[y] <= ret) y++;
	x++;y--;
	rvs(x, y);
}

void solve(int l, int r)
{
	if (l >= r) return;
	bool flag = 1;
	REP(i, l + 1, r)
		if (a[i - 1] > a[i])
		{
			flag = 0;
			break;
		}
	if (flag) return;
	else
	{
		ret = a[rand() % (r - l + 1) + l];
		work(l, r);
		DREP(i, r, l)
			if (a[i] <= ret)
			{
				solve(l, i);
				solve(i + 1, r);
				return;
			}
	}
}

int main()
{
#ifdef CraZYali
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	cin >> n;
	srand(n);
	REP(i, 1, n) scanf("%d", a + i);
	
//	cheat::work();
	solve(1, n);
	printf("-1 -1");

	return 0;
}
