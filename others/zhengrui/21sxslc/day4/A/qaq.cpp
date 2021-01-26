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

#include <bits/extc++.h>//ext/pb_ds/hash_table.hpp>
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

__gnu_pbds :: gp_hash_table <i64, int> v;
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

const int maxM = 14348907;
namespace mysort
{
	const int w = 8, B = (1 << w) - 1;

	const int maxn = maxM;
	int cnt[B + 1];
	pair <i64, int> pool[maxM], *str[B + 1];

	void sort(pair <i64, int> *a, int n)
	{
		int times = 6;//32 / w;
		REP(j, 0, times - 1)
		{
			REP(i, 0, n - 1) cnt[(a[i].fi >> (j * w)) & B]++;
			str[0] = pool;
			REP(i, 1, B) str[i] = str[i - 1] + cnt[i - 1], cnt[i - 1] = 0;
			REP(i, 0, n - 1) *(str[(a[i].fi >> (j * w)) & B]++) = a[i];
			REP(i, 0, n - 1) swap(a[i], pool[i]);
//			std :: swap(a, pool);
		}
	}
}


int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	if (even :: judge()) return even :: main();
	if (n <= 3) {puts("No");return 0;}

	static int ta[maxn];
	REP(i, 1, n) id[i] = i;
	random_shuffle(id + 1, id + 1 + n);
	REP(i, 1, n) ta[i] = a[id[i]];
	swap(a, ta);

	const int N = 1 << n;
	const int B = n + 1 >> 1;
	cerr << B << endl;
	REP(i, 1, max(n - B, B)) LG[1 << i] = i;
	REP(i, 1, (1 << max(n - B, B)) - 1) cnt[i] = cnt[i >> 1] + (i & 1);
	REP(i, 1, (1 << B) - 1) sum[i] = sum[i & (i - 1)] + a[LG[i & -i] + 1];
	i64 tot = 0;
	int nN = 0;

	static pair <i64, int> f1[maxM], f2[maxM];
	int m1 = 0, m2 = 0;

	const i64 delta = 3e10;
	REP(s1, 0, (1 << B) - 1)
		for (int s2 = s1; ; s2 = (s2 - 1) & s1)
		{
			f1[m1++] = make_pair((delta + sum[s1 ^ s2] - sum[s2]) << 5 | (cnt[s1 ^ s2] - cnt[s2] + B), mp(s1 ^ s2, s2));
			//			v[(sum[s1 ^ s2] - sum[s2]) << 5 | (cnt[s1 ^ s2] - cnt[s2] + n)] = mp(s1 ^ s2, s2);
			if (!s2) break;
		}
	REP(i, 1, (1 << n - B) - 1) sum[i] = sum[i & (i - 1)] + a[LG[i & -i] + 1 + B];
	REP(s1, 0, (1 << n - B) - 1)
		for (int s2 = s1; ; s2 = (s2 - 1) & s1)
		{
			f2[m2++] = make_pair((delta - sum[s1 ^ s2] + sum[s2]) << 5 | (-cnt[s1 ^ s2] + cnt[s2] + B), mp(s1 ^ s2, s2));
			//			auto it = v.find((-sum[s1 ^ s2] + sum[s2]) << 5 | (-cnt[s1 ^ s2] + cnt[s2] + n));
			//			if (it != v.end()) report((s1 ^ s2) << B | getfi(it -> se), s2 << B | getse(it -> se));
			if (!s2) break;
		}
	CLOCK;
	mysort::sort(f1, m1);
	mysort::sort(f2, m2);
	for (int i = 0, j = 0; i < m1; i++)
	{
		while (j < m2 - 1 && f2[j].fi < f1[i].fi) j++;
		if (j == m2 - 1 && f2[j].fi < f1[i].fi) break;
		if (f1[i].fi == f2[j].fi) report(getfi(f1[i].se) | (getfi(f2[j].se) << B), getse(f1[i].se) | (getse(f2[j].se) << B));
	}
	puts("No");
	CLOCK;
	return 0;
}
