#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, inf = 2e9;

int n, q;
int a[maxn], b[maxn];

int read()
{
	char c = getchar();int ans = 0;
	while (!isdigit(c)) c = getchar();
	while ( isdigit(c)) ans = ans * 10 + (c - 48), c = getchar();
	return ans;
}
namespace bf
{
	int main()
	{
		while (q--)
		{
			int t = read();
			REP(i, 1, n) if (a[i] <= t) swap(a[i], b[i]);
		}
		long long ans = 0;
		REP(i, 1, n) ans += a[i];
		cout << ans << endl;
		return 0;
	}
}
#define vi vector <int>
#define vb vector <bool>
namespace blk
{
	inline int get_id(const vi &v, int x) {return lower_bound(v.begin(), v.end(), x) - v.begin();}
	int blg[maxn], L[maxn], R[maxn], t[maxn], tot;
	struct seg
	{
		vi num;
		vector <vb > keep;
		seg() {}
		seg(const vi &num, const vector <vb > &keep) : num(num), keep(keep) {}
//		inline bool stable2(int x, int y) {return keep[x][y];}
//		inline bool stable(int x, int y) {return keep[id(num, x)][id(num, y)];}
	}mem[maxn];
	inline vi merge(const vi &A, const vi &B)
	{
		int n = A.size(), m = B.size(), i = 0, j = 0, k = 0;
		vi C(n + m);
		while (i < n && j < m)
			if (A[i] < B[j]) C[k++] = A[i++];
			else C[k++] = B[j++];
		while (i < n) C[k++] = A[i++];
		while (j < m) C[k++] = B[j++];
		C.resize(unique(C.begin(), C.end()) - C.begin());
		return C;		
	}
	vi num;vector <vb > keep;
	seg build(int l, int r)
	{
		if (l == r)
		{
			vi num(2);vector <vb > keep;
			num[0] = t[l];num[1] = inf;
			REP(i, 0, 1)
				keep.emplace_back(vb(2, i));
		printf("%d %d\n", l, r);
		int siz = 2;
		REP(i, 0, siz - 1) printf("%d%c", num[i], i == end_i ? '\n' : ' ');
		REP(i, 0, siz - 1) REP(j, 0, siz - 1) printf("%d%c", (int)keep[i][j], j == end_j ? '\n' : ' ' );
			return seg(num, keep);
		}
		int mid = l + r >> 1;
		auto LHS = build(l, mid), RHS = build(mid + 1, r);
		num = merge(LHS.num, RHS.num);int siz = num.size();
		keep.resize(siz);
		static int Li[maxn], Ri[maxn];

		for (int i = 0, li = 0, ri = 0; i < siz; i++)
		{
			while (LHS.num[li] < num[i]) li++;Li[i] = li;
			while (RHS.num[ri] < num[i]) ri++;Ri[i] = ri;
		}

		int lai = 0, rai = 0;
		vb res(siz, 0);
		REP(i, 0, siz - 1)
		{
			int lbi = 0, rbi = 0;
			REP(j, 0, siz - 1)
			{
				bool flg = 1;
				int ra = num[i], rb = num[j];

				int li = Li[i], ri = Ri[i], lj = Li[j], rj = Ri[j];

				if (!LHS.keep[li][lj]) swap(ri, rj), flg ^= 1;//stable2(li, lj)) swap(ri, rj), flg ^= 1;
				if (!RHS.keep[ri][rj]) flg ^= 1;//stable2(ri, rj)) flg ^= 1;
				res[j] = flg;
			}
			keep[i] = res;//.emplace_back(res);
		}
		printf("%d %d\n", l, r);
		REP(i, 0, siz - 1) printf("%d%c", num[i], i == end_i ? '\n' : ' ');
		REP(i, 0, siz - 1) REP(j, 0, siz - 1) printf("%d%c", (int)keep[i][j], j == end_j ? '\n' : ' ' );
		return seg(num, keep);
	}
	const int B = 900, maxTOT = maxn / B + 5;
	pair <int, int> tb[maxn << 1];int m;
	int main()
	{
		REP(i, 1, q) blg[i] = (i - 1) / B + 1;tot = blg[q];
		REP(i, 1, q) R[blg[i]] = i;
		DEP(i, q, 1) L[blg[i]] = i;
		REP(i, 1, q) t[i] = read();
		REP(i, 1, n)
		{
			tb[++m] = make_pair(a[i], i << 1);
			tb[++m] = make_pair(b[i], i << 1 | 1);
		}
		sort(tb + 1, tb + 1 + m);
		long long ans = 0;
		static int flg[maxn];
		REP(j, 1, tot)
		{
			const seg mem = build(L[j], R[j]);
			static int Id[2][maxn];
			int p = 0;
			REP(i, 1, m)
			{
				int x = tb[i].first, k = tb[i].second & 1, pos = tb[i].second >> 1;
				while (mem.num[p] < x) p++;
				Id[k][pos] = p;
			}
			REP(i, 1, n)
				if (!mem.keep[Id[flg[i]][i]][Id[!flg[i]][i]]) flg[i] ^= 1;
		}
		REP(i, 1, n) if (flg[i]) ans += b[i];else ans += a[i];
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("good.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) a[i] = read(), b[i] = read();
	bool flg = 1;REP(i, 1, n) if (max(a[i], b[i]) > 100) flg = 0;
	return blk :: main();
	return 0;
}

