/*
	Problem:	C.cpp
	Time:		2021-02-21 09:00
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bits/extc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int a, b, c, N, n;
#define vi vector <int>
#define pii pair <int, int>

vi split(int x)
{
	if (!x) return vi(1, 0);
	vi res;
	while (x)
	{
		int y = sqrt(x);
		res.emplace_back(y);
		x -= y * y;
	}
	return res;
}

namespace same
{
	int main()
	{
		auto va = split(a);
		for (int i : va) b -= i * i;
		auto vb = split(b);
		cout << va.size() + vb.size() << endl;
		for (auto i : va) cout << i << ' ';REP(i, 1, vb.size()) cout << 0 << ' ' ;cout << '\n';
		for (auto i : va) cout << i << ' ';for (auto i : vb) cout << i << ' ' ; cout << '\n';
		return 0;
	}
}
const double eps = 1e-8;
#define gg(a, b, c) ((a + b < c + c) || (c >= eps && (double)a / c * b / c < 1))
/*
inline bool gg(int a, int b, int c)
{
	if (a + b < 2 * c) return 1;
	if (c >= eps && (double)a / c * b / c < 1. - eps) return 1;
	return 0;
}
*/
int flag = 0, flag2;
namespace bf
{
	int x[30], y[30];
	__gnu_pbds :: gp_hash_table <unsigned int, __gnu_pbds :: null_type > MEM;
//	unordered_set <unsigned int> MEM;
	void output(int n)
	{
		if (!n)
			puts("1\n0\n0");
		else
		{
			cout << n << endl;
			if (flag2) swap(x, y);
			REP(i, 1, n) printf("%lld%c", x[i], i == end_i ? '\n' : ' ');
			if (flag) REP(i, 1, n) y[i] = -y[i];
			REP(i, 1, n) printf("%lld%c", y[i], i == end_i ? '\n' : ' ');
		}
		cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
		exit(0);
	}
	const unsigned int base = 1e9 + 7, bb = base * base;
	void dfs(int n, int la, int lb, int lc)
	{
		static int cnt = 0;cnt++;cerr << cnt << endl;
		if (!la && !lb && !lc)
		{
			output(n);
			exit(0);
		}
//		if (gg(la, lb, lc)) return;
		if (!la)
		{
			if (lc) return;
			auto v = split(lb);
			REP(i, 1, v.size())
			{
				++n;
				x[n] = 0;
				y[n] = v[i - 1];
			}
			output(n);
		}
		if (!lb)
		{
			if (lc) return;
			auto v = split(la);
			REP(i, 1, v.size())
			{
				++n;
				y[n] = 0;
				x[n] = v[i - 1];
			}
			output(n);
		}
		if (la < lb)
		{
			swap(la, lb);
			swap(x, y);
			flag2 ^= 1;
		}
		unsigned int sta = la + lb * base + lc * bb;
		if (MEM.find(sta) != MEM.end()) return;MEM.insert(sta);
//		if (MEM.find(make_pair(la, make_pair(lb, lc))) != MEM.end()) return;
//		MEM.insert(make_pair(la, make_pair(lb, lc)));
		int lima = sqrt(la), limb = sqrt(lb);
		++n;
		int qaq = sqrt(la + lb - 2 * lc);
		REP(u, -lima, -1)
		{
			int na = la - u * u;
			int L = max(lc / u, -limb), R = limb;
			L = max(L, u - qaq);
			R = min(R, u + qaq);
			REP(v, L, R) //if ((u || v))// && lc >= u * v)
			{
				int nb = lb - v * v, nc = lc - u * v;
				if (gg(na, nb, nc)) continue;
				x[n] = u;y[n] = v;
				dfs(n, na, nb, nc);
			}
		}
		REP(u, 0, 0)
		{
			int na = la - u * u;
			int L = -limb, R = limb;
			L = max(L, u - (int)qaq);
			R = min(R, u + (int)qaq);
			REP(v, L, R) if (v)// && lc >= u * v)
			{
				int nb = lb - v * v, nc = lc - u * v;
				if (gg(na, nb, nc)) continue;
				x[n] = u;y[n] = v;
				dfs(n, na, nb, nc);
			}
		}
		return;
		REP(u, 1, lima)
		{
			int na = la - u * u;
			REP(v, -limb, min(lc / u, limb)) //if ((u || v))// && lc >= u * v)
			{
				int nb = lb - v * v, nc = lc - u * v;
				if (gg(na, nb, nc)) continue;
				x[n] = u;y[n] = v;
				dfs(n, na, nb, nc);
			}
		}
	}
	int main()
	{
		dfs(0, a, b, c);
		puts("-1");
		return 0;
	}
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> a >> b >> c >> N;
	if (a < 0 || b < 0) {puts("-1");return 0;}
	if (gg(a, b, c))
	{
		puts("-1");
		return 0;
	}
	if (a == c) return same :: main();
	if (c < 0) c = -c, flag = 1;
	return bf :: main();
	return 0;
}
