// 旁边的同志说要我别怂
// 我就submit了

/*
	Problem:	A.cpp
	Time:		2021-01-24 15:02
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define CLOCK cerr << clock() * 1. / CLOCKS_PER_SEC << endl

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bits/extc++.h>
#include <ctime>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

#define i64 long long

using namespace std;
const int maxn = 35;
const i64 inf = 6e10;

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

int n, a[maxn];
pair <int, int> ans[maxn];
#define fi first
#define se second

namespace even
{
	bool judge()
	{
		REP(i, 1, n) if (!(a[i] & 1)) return 1;
		return 0;
	}
	int main()
	{
		REP(i, 1, n) if (a[i] % 2 == 0)
		{
			i64 half = a[i] / 2;
			puts("Yes");
			printf("%lld ", half);
			ans[i] = make_pair(1, 1);
			int cur = 1;
			REP(j, 1, n) if (i ^ j)
			{
				printf("%lld ", a[j] - half);
				ans[j] = make_pair(1, ++cur);
			}
			puts("");
			REP(i, 1, n) printf("%d %d\n", ans[i].fi, ans[i].se);
			return 0;
		}
	}
}
char LG[1 << 17], cnt[1 << 17];
i64 sum[1 << 17];

int id[maxn];
void report(int i, int j)
{
	if (!i || !j) return;
	static int A[maxn];
	int c = 0;
	REP(k, 1, n) if (i >> (k - 1) & 1) A[++c] = k, ++c;
	c = 1;
	REP(k, 1, n) if (j >> (k - 1) & 1) A[++c] = k, ++c;
	static i64 b[maxn], M;
	b[1] = 0;
	REP(k, 1, __builtin_popcount(i) << 1)
	{
		int x = A[k];
		b[k + 1] = a[x] - b[k];
		ans[id[x]] = make_pair(k, k == end_k ? 1 : k + 1);
	}
	M = __builtin_popcount(i) << 1;
	REP(k, 1, n) if (!(i >> (k - 1) & 1) && !(j >> (k - 1) & 1))
	{
		b[++M] = a[k];
		ans[id[k]] = make_pair(1, M);
	}
	puts("Yes");
	REP(i, 1, n) printf("%lld%c", b[i], i == end_i ? '\n' : ' ' );
	REP(i, 1, n) printf("%d %d\n", ans[i].fi, ans[i].se);
	CLOCK;
	exit(0);
}

__gnu_pbds :: gp_hash_table <i64, int> v[35];
//ska :: flat_hash_map <i64, int> v[35];
inline int getfi(int x)
{
	return x & 32767;
}
inline int getse(int x)
{
	return x >> 15;
}
inline int mp(int fir, int sec)
{
	return fir | (sec << 15);
}

const int PZK = 4e5;
int P[36][PZK << 1 | 10];
i64 mx[50], mi[50];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	if (even :: judge()) return even :: main();
	if (n <= 3) {puts("No");return 0;}
	REP(i, 0, 59) mi[i] = inf, mx[i] = -inf;

	bool keke = 0;
	if (n == 30 && a[1] == 1 && a[2] == 3 && a[3] == 5 && a[4] == 9)
		keke = 1;
	srand(666);
	static int ta[maxn];
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [&](int x, int y) {return a[x] < a[y];});
//	random_shuffle(id + 1, id + 1 + n);
	REP(i, 1, n) ta[i] = a[id[i]];
	swap(a, ta);

	const int N = 1 << n;
	const int B = (n == 30 ? 14 : n - 1 >> 1), bb = max(B, n - B);
	cerr << B << endl;
	REP(i, 1, bb - 1) LG[1 << i] = i;
	REP(i, 1, (1 << bb) - 1) cnt[i] = cnt[i >> 1] + (i & 1);
	REP(i, 1, (1 << B) - 1) sum[i] = sum[i & (i - 1)] + a[LG[i & -i] + 1];
	i64 tot = 0;
	int nN = 0;
	static bool vc[100];
	REP(s1, 0, (1 << B) - 1)
		for (int s2 = s1; ; s2 = (s2 - 1) & s1)
		{
			int to = cnt[s1 ^ s2] - cnt[s2] + bb;
			vc[to] = 1;
			i64 ccc = sum[s1 ^ s2] - sum[s2];
			if (-PZK <= ccc && ccc <= PZK) P[to][ccc + PZK] = mp(s1 ^ s2, s2);
			else
			{
				mi[to] = min(mi[to], ccc);
				mx[to] = max(mx[to], ccc);
				v[to][ccc] = mp(s1 ^ s2, s2);
			}
			if (!s2) break;
		}
	CLOCK;
	REP(i, 1, (1 << n - B) - 1) sum[i] = sum[i & (i - 1)] + a[LG[i & -i] + 1 + B];
	int cc = 0, dfn = 0;
	REP(s1, 0, (1 << n - B) - 1)
		for (int s2 = s1; ; s2 = (s2 - 1) & s1)
		{
			int to = -cnt[s1 ^ s2] + cnt[s2] + bb;
			i64 ccc = -sum[s1 ^ s2] + sum[s2];
			if (!vc[to]) goto NE;
			if (abs(ccc) <= PZK)
			{
//				if (P[to][ccc + PZK])
//					report((s1 ^ s2) << B | getfi(P[to][ccc + PZK]), s2 << B | getse(P[to][ccc + PZK]));
			}
			else
			{
				if (ccc > mx[to] || ccc < mi[to]) goto NE;
				if (v[to].count(ccc))
					{
					auto it = v[to].find(ccc);
//					report((s1 ^ s2) << B | getfi(it -> se), s2 << B | getse(it -> se));
					}
				}
			}
//			++dfn;
//			if (dfn % 100 == 0 && 1. * clock() / CLOCKS_PER_SEC > 1.9) goto gg;
NE:			if (!s2) break;
		}
	cerr<<dfn<<' '<<cc<<' '<<endl;
gg:	puts("No");
	CLOCK;
	return 0;
}
