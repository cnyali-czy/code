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

int m, n, k;
char s[150];
int a[150], ans;

void dfs(int pos, int al)
{
	if (ans >= 2) return;
	if (pos >= n)
	{
		if (al) ans++;
		return ;
	}
	pos++;
	if (a[pos]) dfs(pos, al);
	else
	{
		set <int> S;
		REP(i, 1, 3) S.insert(i);
		if (pos > 1 && a[pos - 1]) S.erase(a[pos - 1]);
		if (pos < n && a[pos + 1]) S.erase(a[pos + 1]);
		for (set<int> :: iterator it = S.begin(); it != S.end() ; it++)
		{
			a[pos] = *it;
			dfs(pos + 1, al + 1);
			if (ans >= 2) return;
		}
		a[pos] = 0;
	}
}

int main()
{
#ifdef CraZYali
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	scanf("%d\n%s", &n, s + 1);
	a[0] = -1;
	a[n + 1] = -1;
	REP(i, 1, n)
		if (s[i] == 'C') a[i] = 1;
		else if (s[i] == 'M') a[i] = 2;
		else if (s[i] == 'Y') a[i] = 3;
	REP(i, 1, n - 1)
		if (a[i] && a[i] == a[i + 1])
		{
			cout << "No";
			return 0;
		}
	dfs(0, 0);
	if (ans >= 2) printf("Yes");
	else printf("No");
	return 0;
}
