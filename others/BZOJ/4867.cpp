/*
	Problem:	4867.cpp
	Time:		2020-11-29 20:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, inf = 2000000;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q, len;
int siz[maxn], a[maxn], dl[maxn], dr[maxn], ra[maxn], dfs_clock;
pair <int, int> b[maxn];

void dfs(int x)
{
	siz[x] = 1;
	dl[x] = ++dfs_clock;
	for (int i = bg[x]; i; i = ne[i])
	{
		a[to[i]] += a[x];
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
	dr[x] = dl[x] + siz[x] - 1;
}

int blg[maxn], L[maxn], R[maxn], tag[maxn];

int cnt(int l, int r, int val)
{
	int bl = blg[l], br = blg[r], res = 0;
	if (bl == br)
	{
		REP(i, l, r) res += (a[i] + tag[bl] <= val);
	}
	else
	{
		REP(i, l, R[bl]) res += (a[i] + tag[bl] <= val);
		REP(i, L[br], r) res += (a[i] + tag[br] <= val);
		REP(i, bl + 1, br - 1)
		{
			int cur = upper_bound(b + L[i], b + R[i] + 1, make_pair(val - tag[i] + 1, 0)) - b - L[i];
			res += cur;
		}
		return res;
	}
	return res;
}
int query(int ql, int qr, int k)
{
	if (qr - ql + 1 < k) return -1;
	int l = 1, r = inf, res = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (cnt(ql, qr, mid) >= k)
		{
			res = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return res;
}
void bf(int l, int r, int k)
{
	int bl = blg[l];
	static pair <int, int> A[maxn], B[maxn];
	int ta = 0, tb = 0, i = 1, j = 1, cur = L[bl] - 1;
	REP(i, L[bl], R[bl])
		if (l <= b[i].second && b[i].second <= r) A[++ta] = make_pair(b[i].first + k, b[i].second);
		else B[++tb] = b[i];
	while (i <= ta && j <= tb)
		if (A[i] < B[j]) b[++cur] = A[i++];
		else b[++cur] = B[j++];
	while (i <= ta) b[++cur] = A[i++];
	while (j <= tb) b[++cur] = B[j++];
	REP(i, L[bl], R[bl]) a[b[i].second] = b[i].first;
}
void update(int l, int r, int k)
{
	int bl = blg[l], br = blg[r];
	if (bl == br) bf(l, r, k);
	else
	{
		bf(l, R[bl], k);
		bf(L[br], r, k);
		REP(i, bl + 1, br - 1) tag[i] += k;
	}
}

int main()
{
#ifdef CraZYali
	file("4867");
#endif
	n = read<int>();q = read<int>();len = read<int>();
	REP(i, 2, n)
	{
		add(read<int>(), i);
		a[i] = read<int>();
	}
	dfs(1);
	REP(i, 1, n) ra[dl[i]] = a[i];
	swap(a, ra);
	const int B = 900;
	REP(i, 1, n) blg[i] = (i - 1) / B + 1;
	REP(i, 1, n) R[blg[i]] = i;
	DEP(i, n, 1) L[blg[i]] = i;
	REP(i, 1, n) b[i] = make_pair(a[i], i);
	REP(i, 1, blg[n]) sort(b + L[i], b + R[i] + 1);
	while (q--)
	{
		int opt = read<int>(), x = read<int>(), k = read<int>();
		
		if (opt == 1)
		{
			printf("%d\n", query(dl[x], dr[x], k));
		}
		else
		{
			update(dl[x], dr[x], k);
		}
	}
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
