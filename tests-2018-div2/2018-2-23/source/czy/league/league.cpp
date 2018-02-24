#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50 + 5;

int m, n, k;
char a[maxn][maxn];

#define node pair<int, int>
#define name first
#define s second
node t[maxn];
inline bool cmp(node A, node B) {return A.s > B.s || A.s == B.s && A.name < B.name;}

int main()
{
	freopen("league.in", "r", stdin);
	freopen("league.out", "w", stdout);
	scanf("%d\n", &n);
	REP(i, 1, n)
	{
		REP(j, 1, n)
			a[i][j] = getchar();
		if (i ^ n) getchar();
	}
	REP(i, 1, n) t[i].name = i;
	REP(i, 1, n)
	{
		REP(j, 1, n)
			if (a[i][j] == 'W') t[i].s += 3;
			else if (a[i][j] == 'D') t[i].s++, t[j].s++;
			else t[j].s += 3;
	}
	sort(t + 1, t + 1 + n, cmp);
	int now = t[1].s;
	REP(i, 1, n)
		if (t[i].s == now) printf("%d ", t[i].name);
		else break;
	return 0;
}
