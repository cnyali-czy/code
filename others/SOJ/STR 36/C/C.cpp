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

#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
#define double long double
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
		while (y * y > x) y--;
		while ((y + 1) * (y + 1) <= x) y++;
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
#define gg(a, b, c) ((a + b < c + c) || (c >= eps && (__int128)a * b < (__int128)c * c))
int flag = 0, flag2;
const int inf = 1e18;
const double eps = 1e-8;
void write(__int128 x)
{
	if (x < 0) x = -x, cerr << '-';
	if (x / 10) write(x / 10);
	cerr << (char)(x % 10 + 48);
}
pair <int, int> good(__int128 A, __int128 B, __int128 C) // Ax ^ 2 + Bx <= C
{
//	if (A > 1e9 || B > 1e9 || C > 1e9) return make_pair(-inf, inf);
	if (!A)
	{
		if (B > 0)	return make_pair(-inf, C / B);
		else		return make_pair(C / B,  inf);
	}
	double delta = (double)B * B + (double)4 * A * C;
	if (delta < 0) return make_pair(0, -1);
	double d = sqrtl(delta);
	double L = (-B - d) / 2 / A, R = (-B + d) / 2 / A;
	int ansl = ceil(L), ansr = floor(R);
	if (C > 0) {DEBUG;exit(0);}
//	while (ansl <= ansr && (double)A / C * A * ansl * ansl + (double)B / C * ansl < 1 - eps) ansl++;
//	while (ansr >= ansl && (double)A / C * A * ansr * ansr + (double)B / C * ansr < 1 - eps) ansr--;
	REP(i, ansl, ansr) if (0)
	{
		double x = i;
		double y = A * x * x + B * x - C;
		if (y > 0)
		{
			DEBUG;
			exit(0);
		}
	}
	return make_pair(ansl, ansr);
}
namespace bf
{
	int x[30], y[30];
	__gnu_pbds :: gp_hash_table <unsigned int, __gnu_pbds :: null_type > MEM;
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
#ifdef CraZYali
		cerr << n << ' ' << la << ' ' << lb << ' ' << lc << ' ' << x[n] << ' ' << y[n] << endl;
		static int cnt = 0;cnt++;cerr << cnt << endl;
#endif
		if (!la && !lb && !lc)
		{
			output(n);
			exit(0);
		}
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
		if (la > lb)
		{
			swap(la, lb);
			swap(x, y);
			flag2 ^= 1;
		}
		unsigned int sta = la + lb * base + lc * bb;
		if (MEM.find(sta) != MEM.end()) return;MEM.insert(sta);
		int lima = sqrt(la), limb = sqrt(lb);
		++n;
		int qaq = sqrt(la + lb - 2 * lc);
		REP(u, -lima, -1)
		{
			int na = la - u * u;
			int L = max((lc - u + 1) / u, -limb), R = limb;
			
			if (L * u > lc) {DEBUG;exit(0);}
			auto ccc = good(la, (__int128)-2 * lc * u, (__int128)na * lb - (__int128)lc * lc);
			L = max(L, ccc.first);R = min(R, ccc.second);
			L = max(L, u - qaq);R = min(R, u + qaq);
//			if (L >= R) cerr << u << ' ' << u + lima << endl;
			bool tst = 0;

			REP(v, L, R)
			{
				int nb = lb - v * v, nc = lc - u * v;
//				DEBUG;
				if (gg(na, nb, nc))
				{
//					cerr<<"!!!: "<<u<<' '<< la<<' '<<lb<<' '<<lc<<' '<<ccc.first<<' '<<ccc.second<<' ';write((__int128)na*nb-(__int128)nc*nc);cerr<<endl;
					continue;
				}
				x[n] = u;y[n] = v;
				dfs(n, na, nb, nc);
			}
		}
		return ;
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
