#define REP(i, s, e) for (int i = s; i <= e; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 10;

int n, pos;
struct line
{
	int l, r, id;
}l[maxn];
bool cmp(line A, line B) {return A.r < B.r;} 
int dp[maxn], frm[maxn], ans[maxn], top;

int b[maxn << 2], cur;
unordered_map <int, int> to;
void turn()
{
	REP(i, 1, n) b[i] = l[i].l, b[i + n] = l[i].r, b[i + n + n] = l[i].l + 1, b[i + n + n + n] = l[i].r + 1;
	sort(b + 1, b + 1 + 4 * n);
	REP(i, 1, n * 4)
		if (!to[b[i]]) to[b[i]] = ++cur;
	REP(i, 1, n) l[i] = (line){to[l[i].l], to[l[i].r], i};
}

namespace cheat
{
	void work()
	{

	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d%d", &l[i].l, &l[i].r), l[i].id = i;
	turn();
	sort(l + 1, l + 1 + n, cmp);
	if (n <= 2000)
	{
		REP(i, 1, n)
		{
			dp[i] = 1;
			REP(j, 1, i - 1)
				if (l[j].r < l[i].l && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1, frm[i] = j;
		}
		pos = 1;
		REP(i, 2, n) if (dp[i] > dp[pos] || dp[i] == dp[pos] && better(i, pos)) pos = i;
		printf("%d\n", dp[pos]);
		top = 0;
		while (pos) ans[++top] = l[pos].id, pos = frm[pos];
		sort(ans + 1, ans + 1 + top);
		REP(i, 1, top) printf("%d%c", ans[i], i == top ? '\n' : ' ');
	}
	else cheat::work();
	return 0;
}
