/*
	Problem:	SA.cpp
	Time:		2020-02-17 16:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;


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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

namespace run
{
	using namespace std;

	struct SuffixArray {
		int n;
		vector<int> x, y, r, sa, ht, rk;
		SuffixArray(const char *s, int m = 256) : n(strlen(s) + 1), x(n), y(n), r(n), sa(n + 1), ht(n), rk(n + 1) {
			for (int i = 0; i < n; i++) r[i] = s[i];
			init(m);
		}

		bool cmp(vector<int> &r, int a, int b, int j) {
			return r[a] == r[b] && r[a + j] == r[b + j];
		}

		void init(int m) {
			vector<int> sum(max(m, n));
			int i, j, p;
			for (i = 0; i < n; i++) sum[ x[i] = r[i] ]++;
			for (i = 1; i < m; i++) sum[i] += sum[i - 1];
			for (i = n - 1; i > -1; i--) sa[ --sum[ x[i] ] ] = i;

			for (p = 0, j = 1; p < n; j <<= 1) {
				for (p = 0, i = n - j; i < n; i++) y[p++] = i;
				for (i = 0; i < n; i++)
					if (sa[i] >= j) y[p++] = sa[i] - j;

				for (i = 0; i < m; i++) sum[i] = 0;
				for (i = 0; i < n; i++) sum[ x[i] ]++;
				for (i = 1; i < m; i++) sum[i] += sum[i - 1];
				for (i = n - 1; i > -1; i--) sa[ --sum[ x[ y[i] ] ] ] = y[i];

				x.swap(y);
				p = 1; x[ sa[0] ] = 0;
				for (i = 1; i < n; i++)
					if (cmp(y, sa[i - 1], sa[i], j)) x[ sa[i] ] = p - 1;
					else x[ sa[i] ] = p++;
				m = p;
			}
			n--;
			for (i = 0; i < n; i++) sa[i] = sa[i + 1];
			sa.resize(n);

			getHeight();
		}

		void getHeight() {
			for (int i = 0; i < n; i++) printf("%d%c", sa[i], i == n - 1 ? '\n' : ' ');
			for (int i = 0; i < n; i++) rk[ sa[i] ] = i;
			rk[n] = -1;

			int p = 0;
			for (int i = 0; i < n; i++) {
				if (p != 0) p--;
				if (rk[i] == 0) continue;
				int j = sa[ rk[i] - 1 ];
				while (r[i + p] == r[j + p]) p++;
				ht[ rk[i] ] = p;
			}
		}

		int &operator[](const int &x) {
			return sa[x];
		}
	} ;

	void bound(SuffixArray &f, int L, int R, int X, int Y, int &x, int &y, int offset) {
		int i = L, j = R, mid;
		while (i <= j) {
			mid = (i + j) >> 1;
			if (f.rk[ f[mid] + offset ] < X) i = mid + 1;
			else j = mid - 1;
		}
		x = i;

		i = L, j = R;
		while (i <= j) {
			mid = (i + j) >> 1;
			if (f.rk[ f[mid] + offset ] > Y) j = mid - 1;
			else i = mid + 1;
		}
		y = j;
	}

	int main() {
		static const int maxn = 5e5 + 7;    
		static char S[maxn], T[maxn];
		static int L[maxn], R[maxn];
		static int Lc[256], Rc[256];

		scanf("%s", S);
		SuffixArray f(S);
		int n = strlen(S);
		for (int i = 'a'; i <= 'z'; i++) Lc[i] = n - 1, Rc[i] = 0;
		for (int i = 0; i < n; i++) {
			Lc[ S[ f[i] ]] = min(Lc[ S[ f[i] ] ], i);
			Rc[ S[ f[i] ]] = max(Rc[ S[ f[i] ] ], i);
		}
		for (int i = 0; i < n; i++) printf("%d%c", f[i], i == n - 1 ? '\n' : ' ');
		for (int i = 0; i < n; i++) printf("%d%c", f.rk[i], i == n - 1 ? '\n' : ' ');
		// for (int i = 'a'; i <= 'z'; i++) cout << Lc[i] << ' ' << Rc[i] << endl;

		// for (int i = 0; i < n; i++) {
		//     for (int j = f[i]; j < n; j++) putchar(S[j]);
		//     puts("");
		// }

		int cases;
		scanf("%d", &cases);
		while (cases--) {
			scanf("%s", T);
			int m = strlen(T);
			long long ans = 0;

			L[m] = -1, R[m] = n - 1;
			for (int i = m - 1; i >= 0; i--) {
				bound(f, Lc[ T[i] ], Rc[ T[i] ], L[i + 1], R[i + 1], L[i], R[i], 1);
			}

			int current_L = 0, current_R = n - 1;
			for (int i = 0; i < m; i++) {
				for (int j = 'a'; j <= 'z'; j++) {
					if (j == T[i]) continue;
					int x, y;
					bound(f, current_L, current_R, Lc[j], Rc[j], x, y, i);
					// cout << current_L << ' ' << current_R << ' ' << Lc[j] << ' ' << Rc[j] << ' ' << x << ' ' << y << endl;
					bound(f, x, y, L[i + 1], R[i + 1], x, y, i + 1);
					if (x <= y) ans += y - x + 1;
				}
				bound(f, current_L, current_R, Lc[ T[i] ], Rc[ T[i] ], current_L, current_R, i);
			}

			cout << ans << endl;
		}
		return 0;
	}

}

int main()
{
#ifdef CraZYali
	freopen("SA.in", "r", stdin);
	freopen("std.out", "w", stdout);;
#endif
	return run::main();
}
