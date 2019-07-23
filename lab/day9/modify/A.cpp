#define REP(i, s, e) for (int i = s; i <= e; i++)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 200000 + 10;

#define mid (l + r >> 1)
int n, frm[maxn], last[maxn], dp[maxn], pos;
struct line
{
		int l, r, id;
}q[maxn];
bool cmp(line A, line B) {return A.r < B.r;}
void jump(int x)
{
	int a = x, b = last[x-1], mina(q[a].id), minb(q[b].id);
	while (frm[a] ^ frm[b])
	{
		chkmin(mina, q[a].id), a = frm[a];
		chkmin(minb, q[b].id), b = frm[b];
	}
	chkmin(mina, q[a].id);
	chkmin(minb, q[b].id);
	if(mina < minb) dp[x] = dp[pos] + 1, last[x] = x, frm[x] = last[pos];
	else dp[x] = dp[x-1], last[x] = last[x-1], frm[x] = frm[x-1];
}
int stack[maxn], top;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	sort(q + 1, q + 1 + n, cmp);
	REP(i, 1, n)
	{
		int l(0), r(i-1);
		pos = 0;
		while (l <= r)
			if (q[mid].r < q[i].l)
			{
				pos = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		dp[i] = dp[pos] + 1;
		frm[i] = last[pos];
		if (dp[i] > dp[i-1]) dp[i] = dp[pos] + 1, last[i] = i;
		else if (dp[i] < dp[i-1]) dp[i] = dp[i-1], last[i] = last[i-1];
		else jump(i);
	}
	cout << dp[n] << endl;
	pos = last[n];
	while(pos) stack[++top] = q[pos].id, pos = frm[pos];
	sort(stack + 1, stack + 1 + top);
	REP(i, 1, top) printf("%d%c", stack[i], i == top ? '\n' : ' ');
	return 0;
}
