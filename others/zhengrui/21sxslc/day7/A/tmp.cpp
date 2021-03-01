#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <ctime>
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
const int FUCK = 400 * 1024 * 1024 / 4;
int pool[FUCK], *cur = pool;
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
bool bpool[FUCK], *bcur = bpool;
struct vb
{
	bool *a, n;
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
//		while (N--) a[N] = v;
	}
};
namespace blk
{
	int blg[maxn], L[maxn], R[maxn], t[maxn], tot;

	vi num[maxn << 2];
	vector <vb> keep[maxn << 2];
	inline vi merge(const vi &A, const vi &B)
	{
		int n = A.n, m = B.n, i = 0, j = 0, k = 0;
		static int C[maxn];
		while (i < n && j < m)
			if (A.a[i] < B.a[j]) C[k++] = A.a[i++];
			else C[k++] = B.a[j++];
		while (i < n) C[k++] = A.a[i++];
		while (j < m) C[k++] = B.a[j++];
		k = unique(C, C + k) - C;
		vi res;res.resize(k);
		REP(i, 0, k - 1) res.a[i] = C[i];
		return res;
	}
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

	void build(int p, int l, int r)
	{
		if (l == r)
		{
			num[p].resize(2);
			num[p].a[0] = t[l];num[p].a[1] = inf;
			keep[p].clear();
			REP(i, 0, 1)
			{
				vb x(2, i);
				keep[p].push_back(x);
				//				keep[p].push_back(vb(2, i));
			}
			return;
		}
		build(lson);build(rson);
		num[p] = merge(num[ls], num[rs]);int siz = num[p].n;
		keep[p].resize(siz);
		static int Li[maxn], Ri[maxn];

		for (int i = 0, li = 0, ri = 0; i < siz; i++)
		{
			while (num[ls].a[li] < num[p].a[i]) li++;Li[i] = li;
			while (num[rs].a[ri] < num[p].a[i]) ri++;Ri[i] = ri;
		}

		int lai = 0, rai = 0;
		vb res(siz, 0);
		REP(i, 0, siz - 1)
		{
			int lbi = 0, rbi = 0;
			REP(j, 0, siz - 1)
			{
				bool flg = 1;
				int ra = num[p].a[i], rb = num[p].a[j];

				int li = Li[i], ri = Ri[i], lj = Li[j], rj = Ri[j];

				if (!keep[ls][li].a[lj]) swap(ri, rj), flg ^= 1;//stable2(li, lj)) swap(ri, rj), flg ^= 1;
				if (!keep[rs][ri].a[rj]) flg ^= 1;//stable2(ri, rj)) flg ^= 1;
				res.a[j] = flg;
			}
			keep[p][i] = res;//.emplace_back(res);
		}
	}
	const int B = 1000, maxTOT = maxn / B + 5;
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
			cur = pool;
			bcur = bpool;
			build(1, L[j], R[j]);
			static int Id[2][maxn];
			int p = 0;
			REP(i, 1, m)
			{
				int x = tb[i].first, k = tb[i].second & 1, pos = tb[i].second >> 1;
				while (num[1].a[p] < x) p++;
				Id[k][pos] = p;
			}
			REP(i, 1, n)
				if (!keep[1][Id[flg[i]][i]].a[Id[!flg[i]][i]]) flg[i] ^= 1;
		}
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
	return 0;
}
