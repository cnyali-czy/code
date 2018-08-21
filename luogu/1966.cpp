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
const int maxn = 100000 + 10;
const long long MOD = 99999997;

int m, n, k;

long long ans;

int c[maxn], t[maxn];

void merge(int l, int x, int r)
{
	register int i = l, j = x;
	REP(k, l, r)
		if (j > r || i < x && c[i] < c[j]) t[k] = c[i++];
		else
		{
			t[k] = c[j++];
			ans = (ans + x - i) % MOD;
		}
	REP(i, l, r) c[i] = t[i];
}

void merge_sort(int l, int r)
{
	if (l >= r) return ;
	else
	{
		register int mid = l + r >> 1;
		merge_sort(l, mid);
		merge_sort(mid + 1, r);
		merge(l, mid + 1, r);
	}
}

pair <int, int> a[maxn], b[maxn];
bool cmp_by_val(pair <int, int> A, pair<int, int> B) {return A.first < B.first;}

int main()
{
#ifdef CraZYali
	freopen("1966.in", "r", stdin);
	freopen("1966.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%d", &a[i].first);
		a[i].second = i;
	}
	sort(a + 1, a + 1 + n, cmp_by_val);
	REP(i, 1, n)
	{
		scanf("%d", &b[i].first);
		b[i].second = i;
	}
	sort(b + 1, b + 1 + n, cmp_by_val);
	REP(i, 1, n) c[a[i].second] = b[i].second;

	merge_sort(1, n);

	cout << (ans + MOD) % MOD;

	return 0;
}
