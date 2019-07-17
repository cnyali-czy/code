#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 300000 + 10 << 1, maxnode = maxn * 30;

int n, m, l, r, x, s[maxn];
int rt[maxn], cnt[maxnode], ch[maxnode][2], cur;

void update(int pre, int &p, int val, int pos)
{
	p = ++cur;
	if (pos < 0) return;
	int v = (val >> pos) & 1;
	ch[p][v ^ 1] = ch[pre][v ^ 1];
	update(ch[pre][v], ch[p][v], val, pos - 1);
	cnt[ch[p][v]] = cnt[ch[pre][v]] + 1;
}

int query(int u, int v, int val, int pos)
{
	int ans(0);
	while (pos >= 0)
	{
		bool c = (val >> pos) & 1;
		if (cnt[ch[v][c ^ 1]] > cnt[ch[u][c ^ 1]]) ans += (1 << pos), u = ch[u][c ^ 1], v = ch[v][c ^ 1];
		else u = ch[u][c], v = ch[v][c];
		pos--;
	}
	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4735.in", "r", stdin);
	freopen("4735.out", "w", stdout);
#endif
	cin >> n >> m;
	update(0, rt[0], 0, 25);
	REP(i, 1, n)
	{
		scanf("%d", &x);
		update(rt[i-1], rt[i], s[i] = s[i-1] ^ x, 25);
	}
	while (m--)
	{
		char c = getchar();
		while (c ^ 'A' && c ^ 'Q') c = getchar();
		if (c == 'A')
		{
			scanf("%d", &x);
			n++;
			update(rt[n-1], rt[n], s[n] = s[n-1] ^ x, 25);
		}
		else
		{
			scanf("%d%d%d", &l, &r, &x);x ^= s[n];
			l--;r--;
			if (!l) printf("%d\n", query(0, rt[r], x, 25));
			else printf("%d\n", query(rt[l-1], rt[r], x, 25));
		}
	}
	return 0;
}
