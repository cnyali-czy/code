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

const int maxn = 100010;

int m, n, k;
int a[maxn];

int st[maxn], top;

int main()
{
#ifdef CraZYali
	freopen("1020.in", "r", stdin);
	freopen("1020.out", "w", stdout);
#endif
	while (scanf("%d", &k) != EOF) a[++n] = k;

	st[0] = 1e9;
	REP(i, 1, n)
		if (a[i] <= st[top]) st[++top] = a[i];
		else
		{
			register int l = 1, r = top;
			while (l <= r)
			{
				register int mid = l + r >> 1;
				if (st[mid] < a[i]) r = mid - 1;
				else l = mid + 1;
			}
			st[l] = a[i];
		}
	cout << top << endl;
	
	st[top = 0] = 0;
	REP(i, 1, n)
		if (a[i] > st[top]) st[++top] = a[i];
		else
		{
			register int l = 1, r = top;
			while (l <= r)
			{
				register int mid = l + r >> 1;
				if (st[mid] >= a[i]) r = mid - 1;
				else l = mid + 1;
			}
			st[l] = a[i];
		}
	cout << top << endl;
	return 0;
}
