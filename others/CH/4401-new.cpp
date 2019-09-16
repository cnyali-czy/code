/*
 * File Name:	4401-new.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.16 21:47
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;
const int N = 4e4, maxn = N + 10, siz = (int)sqrt(N);

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)

int n, m, k;
int a[maxn], b[maxn], cnt[maxn];

int tot, belong[maxn], L[maxn / siz], R[maxn / siz], ans[maxn / siz][maxn / siz], qaq[maxn][maxn / siz];

inline void init()
{
	REP(i, 1, n) qaq[a[i]][belong[i] = (i - 1) / siz + 1]++;
	tot = belong[n];
	REP(i, 1, k)
		REP(j, 1, tot) qaq[i][j] += qaq[i][j-1];
	DREP(i, n, 1) L[belong[i]] = i;
	REP(i, 1, n) R[belong[i]] = i;
	REP(i, 1, tot)
	{
		REP(j, 1, k) cnt[j] = 0;
		int &cur = ans[i][i];
		cur = a[L[i]];
		REP(j, L[i], R[i])
		{
			++cnt[a[j]];
			if (cnt[a[j]] > cnt[cur] || cnt[a[j]] == cnt[cur] && a[j] < cur) cur = a[j];
		}
		REP(j, i + 1, tot)
		{
			int &cur = ans[i][j];
			cur = ans[i][j-1];
			REP(k, L[j], R[j])
			{
				++cnt[a[k]];
				if (cnt[a[k]] > cnt[cur] || cnt[a[k]] == cnt[cur] && a[k] < cur) cur = a[k];
			}
		}
	}
}

int main()
{
#ifdef CraZYali
	file("4401-new");
#endif
	cin >> n >> m;
	REP(i, 1, n) b[i] = a[i] = read<int>();
	sort(b + 1, b + 1 + n);
	k = unique(b + 1, b + 1 + n) - b - 1;
	REP(i, 1, n) a[i] = lower_bound(b + 1, b + 1 + k, a[i]) - b;

	init();
	
	int lastans = 0;
	REP(line,1,m)
	{
		int l0(read<int>()), r0(read<int>());
		int l((l0 + lastans - 1) % n + 1), r((r0 + lastans - 1) % n + 1);
		if (l > r) swap(l, r);
		int bl(belong[l]), br(belong[r]), cur(a[l]);
		if (br - bl < 1)
		{
			REP(i, l, r) cnt[a[i]] = 0;
			REP(i, l, r)
			{
				++cnt[a[i]];
				if (cnt[a[i]] > cnt[cur] || cnt[a[i]] == cnt[cur] && a[i] < cur) cur = a[i];
			}
		}
		else
		{
			cur = ans[bl + 1][br - 1];
			cnt[cur] = 0;
			REP(i, l, R[bl]) cnt[a[i]] = 0;
			REP(i, L[br], r) cnt[a[i]] = 0;
			REP(i, l, R[bl]) cnt[a[i]]++;
			REP(i, L[br], r) cnt[a[i]]++;
			int cc = cnt[cur] + (qaq[cur][br-1] - qaq[cur][bl]);
			REP(i, l, R[bl])
			{
				int res = cnt[a[i]] + (qaq[a[i]][br-1] - qaq[a[i]][bl]);
				if (res > cc || res == cc && a[i] < cur) cc = res, cur = a[i];
			}
			REP(i, L[br], r)
			{
				int res = cnt[a[i]] + (qaq[a[i]][br-1] - qaq[a[i]][bl]);
				if (res > cc || res == cc && a[i] < cur) cc = res, cur = a[i];
			}
		}
		printf("%d\n", lastans = b[cur]);
	}
	return 0;
}
