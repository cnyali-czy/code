#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;
const int maxn = 1e6 + 10;

int n, a[maxn], cnt[maxn], ans, tot, A;

int las[maxn],buc[maxn];

void dfs(int x)
{
	if (x == n - 1)
	{
		tot++;
		if (cnt[a[n]]) ans++;
		return;
	}
	x++;
	if (x == 1)
	{
		REP(i, 1, n) 
		{
			cnt[a[i]]--;
			dfs(x);
			cnt[a[i]]++;
		}
	}
	else if (cnt[a[x]])
	{
		cnt[a[x]]--;
		REP(j, 0, cnt[a[x]]) dfs(x);
		cnt[a[x]]++;
	}
	else
	{
		REP(i, 1, n) if (cnt[a[i]])
		{
			cnt[a[i]]--;
			dfs(x);
			cnt[a[i]]++;
		}
	}
}

int main()
{
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	cin >> n;
	REP(i, 1, n) scanf("%d", a + i), cnt[a[i]]++, A = max(A, a[i]);
	REP(i, 1, n) las[a[i]] = i;
//	dfs(0);
//	cout << ans << ' ' << tot << endl;
//	printf("%.10lf\n", ans * 1. / tot);
	static double f[maxn];
	
	DEP(i, n - 1, 1)
	{
		REP(j, i, n) buc[a[j]] = 0;
		REP(j, i, n)
		{
			++buc[a[j]];
			if (las[a[j]] == j)
			{
				if (a[j] == a[1])
				{
					f[i] += buc[a[j]] / (n - i + 1.);
					continue;
				}
				if (a[i] != a[j])
					f[i] += f[j] * buc[a[j]] / (n - i + 1);
				else
					f[i] += 1 / (n - i + 1.);
			}
		}
		if (i % 1000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", n - i, n, (n - i) * 100. / n);
	}
 	printf("%.10lf\n", f[1]);
	return 0;
}
