#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <ctime>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, inf = 2e9;

int n, q;
int a[maxn], b[maxn];

#ifndef CraZYali
#define getchar getchar_unlocked
#endif
inline int read()
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
const int FUCK_ = 1e4, FUCK = 1e6;
int pl[FUCK_], *cur = pl;
struct vi
{
	int *a, n;
	vi() {}
	void resize(int N)
	{
		n = N;
		a = cur;cur += N;
	}
};
bool bpl[FUCK], *bcur = bpl;
struct vb
{
	bool *a;
	int n;
	void resize(int N)
	{
		n = N;
		a = bcur;bcur += N;
	}
	vb() {}
	vb(int N, bool v)
	{
		resize(N);
		REP(i, 0, N - 1) a[i] = v;
	}
};

vb vpl[FUCK_], *vcur = vpl;
struct vvb
{
	vb *a;
	int n;
	void resize(int N)
	{
		n = N;
		a = vcur;vcur += N;
	}
};

namespace blk
{
	const int B = 512, maxTOT = maxn / B + 5;
	int blg[maxn], L[maxn], R[maxn], t[maxn], tot;

	vi num[B << 2];
	vvb keep[B << 2];
	inline vi merge(const vi &a, const vi &b)
	{
		int n = a.n, m = b.n, i = 0, j = 0, k = 0;
		static int C[B];
		while (i < n && j < m)
			if (a.a[i] < b.a[j]) C[k++] = a.a[i++];
			else C[k++] = b.a[j++];
		while (i < n) C[k++] = a.a[i++];
		while (j < m) C[k++] = b.a[j++];
		k = unique(C, C + k) - C;
		vi res;res.resize(k);
		REP(i, 0, k - 1) res.a[i] = C[i];
		return res;
	}
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid (l + r >> 1)

	void build(int p, int l, int r)
	{
		static pair <int, pair <int, int> > stk[6666];int TOP = 0;
		stk[++TOP] = make_pair(p << 1, make_pair(l, r));
		while (TOP)
		{
			int &tp = stk[TOP].first, p = tp >> 1, l = stk[TOP].second.first, r = stk[TOP].second.second;
			if (l == r)
			{
				num[p].resize(2);
				num[p].a[0] = t[l];num[p].a[1] = inf;
				keep[p].resize(2);
				//			keep[p].clear();
				REP(i, 0, 1) keep[p].a[i] = vb(2, i);
				TOP--;
				continue;
			}
			if (tp % 2 == 0)
			{
				tp |= 1;
				stk[++TOP] = make_pair(ls << 1, make_pair(l, mid));
				stk[++TOP] = make_pair(rs << 1, make_pair(mid + 1, r));
				continue;
			}
			TOP--;
			num[p] = merge(num[ls], num[rs]);int siz = num[p].n;
			keep[p].resize(siz);
			static int Li[B], Ri[B];

			for (int i = 0, li = 0, ri = 0; i < siz; i++)
			{
				int x = num[p].a[i];
				while (num[ls].a[li] < x) li++;Li[i] = li;
				while (num[rs].a[ri] < x) ri++;Ri[i] = ri;
			}

			int lai = 0, rai = 0;
			REP(i, 0, siz - 1)
			{
				vb res;res.resize(siz);
				REP(j, 0, siz - 1)
				{
					bool flg = 1;

					int li = Li[i], ri = Ri[i], lj = Li[j], rj = Ri[j];

					if (!keep[ls].a[li].a[lj]) swap(ri, rj), flg = 0;
					res.a[j] = flg ^ (!keep[rs].a[ri].a[rj]);
				}
				keep[p].a[i] = res;//.emplace_back(res);
			}
		}
	}
	pair <int, int> tb[maxn << 1];int m;
	int main()
	{
		REP(i, 1, q) blg[i] = (i - 1) / B + 1;tot = blg[q];
		REP(i, 1, q) R[blg[i]] = i;
		DEP(i, q, 1) L[blg[i]] = i;
		REP(i, 1, q) t[i] = read();
		static int id[maxn];REP(i, 1, n) id[i] = i;sort(id + 1, id + 1 + n, [&](int x, int y){ return a[x] < a[y];});
		static int A[maxn], Bb[maxn];REP(i, 1, n) A[i] = a[id[i]], Bb[i] = b[id[i]];swap(a, A);swap(b, Bb);

		REP(i, 1, n)
		{
			tb[++m] = make_pair(a[i], i << 1);
			tb[++m] = make_pair(b[i], i << 1 | 1);
		}
		sort(tb + 1, tb + 1 + m);
		static int flg[maxn];
		REP(j, 1, tot)
		{
			if (j == 2) cerr << cur - pl << ' ' << bcur - bpl << ' ' << vcur - vpl << ' ' << FUCK << endl;
			cur = pl;bcur = bpl;vcur = vpl;
			build(1, L[j], R[j]);
			static int Id[maxn][2];
			int p = 0;
			REP(i, 1, m)
			{
				int x = tb[i].first, k = tb[i].second & 1, pos = tb[i].second >> 1;
				while (num[1].a[p] < x) p++;
				Id[pos][k] = p;
			}
			REP(i, 1, n) 
				if (!keep[1].a[Id[i][flg[i]]].a[Id[i][!flg[i]]]) flg[i] ^= 1;
		}
		long long ans = 0;
		REP(i, 1, n) if (flg[i]) ans += b[i];else ans += a[i];
		cout << ans << endl;
		cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) a[i] = read(), b[i] = read();
	return blk :: main();
}
