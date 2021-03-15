#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10;

int n, q, a[maxn];

namespace ST
{
	int lg[maxn];
	int pos[17][maxn];
	inline int Min(int x, int y) {return a[x] < a[y] ? x : y;}
	void init()
	{
		REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
		REP(i, 1, n) pos[0][i] = i;
		REP(j, 1, 16)
			REP(i, 1, n - (1 << j) + 1)
			pos[j][i] = Min(pos[j - 1][i], pos[j - 1][i + (1 << j - 1)]);
	}
	inline int query(int l, int r)
	{
		int k = lg[r - l + 1];
		return Min(pos[k][l], pos[k][r - (1 << k) + 1]);
	}
}

int stk[maxn], top, pre[maxn], suf[maxn];
i64 fl[maxn], fr[maxn], gl[maxn], gr[maxn];

int main()
{
#ifdef CraZYali
	freopen("3246.in", "r", stdin);
	freopen("3246.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) scanf("%d", a + i);
	ST :: init();
	REP(i, 1, n)
	{
		while (top && a[stk[top]] > a[i])
			suf[stk[top--]] = i;
		pre[i] = stk[top];stk[++top] = i;
	}
	while (top)
	{
		pre[stk[top]] = stk[top - 1];
		suf[stk[top--]] = n + 1;
	}
	REP(i, 1, n)
	{
		fr[i] = 1ll * a[i] * (i - pre[i]) + fr[pre[i]];
		gr[i] = gr[i - 1] + fr[i];
	}
	DEP(i, n, 1)
	{
		fl[i] = 1ll * a[i] * (suf[i] - i) + fl[suf[i]];
		gl[i] = gl[i + 1] + fl[i];
	}
	while (q--)
	{
		int l, r;scanf("%d%d", &l, &r);
		int p = ST :: query(l, r);
		i64 ans = (p - l + 1ll) * (r - p + 1ll) * a[p];
		ans += gr[r] - gr[p];ans -= fr[p] * (r - p);
		ans += gl[l] - gl[p];ans -= fl[p] * (p - l);
		cout << ans << '\n';
	}
	return 0;
}
