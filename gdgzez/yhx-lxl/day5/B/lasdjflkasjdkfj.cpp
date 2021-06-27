/*
	Problem:	B.cpp
	Time:		2021-06-23 18:49
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#ifdef CraZYali
#include <ctime>
#endif
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 3e5 + 10;

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

int n, q, a[maxn];
namespace bf
{
	void work()
	{
		while (q--)
		{
			int opt = read<int>(), l = read<int>(), r = read<int>();
			if (opt == 1)
			{
				int x = read<int>();
				static int b[maxn];
				REP(i, l, r) b[i] = a[i];
				REP(i, l, r) a[x + i - l] = b[i];
			}
			else if (opt == 2) REP(i, l, r) a[i] >>= 1;
			else
			{
				i64 ans = 0;
				REP(i, l, r) ans += a[i];
				printf("%lld\n", ans);
			}
		}
	}
}
namespace cheat
{
	const int b1 = 500, b2 = 1000;
	int blg[maxn], L[maxn], R[maxn];
	
	struct node
	{
		vector <int> a;
		mutable vector <i64> s;
		mutable int l, r, k;
		node(int l = 0) : l(l) {}
		node(int l, int r, vector <int> a, int k = 0) : l(l), r(r), a(a), k(k)
		{
			if (k <= 30) for (auto &i : a) i >>= k;
			else a = vector <int> (a.size(), 0);
			k = 0;

			s.clear();
			i64 sum = 0;
			auto b = a;
			do
			{
				sum = 0;
				for (auto &i : b) sum += i, i /= 2;
				s.emplace_back(sum);
			}while (sum);
			reverse(s.begin(), s.end());
		}
		inline bool operator < (const node &B) const {return l < B.l;}
	};
	set <node> ssr;
#define IT set <node> :: iterator
	
	IT split(int pos)
	{
		if (pos > n) return ssr.end();
		auto it = ssr.lower_bound(node(pos));
		if (it != ssr.end() && it -> l == pos) return it;
		if (it == ssr.begin()) 
			return ssr.emplace(pos, pos, vector <int> {0}).first;
		--it;
		int l = it -> l, r = it -> r, k = it -> k;
		vector <int> a1, a2, a = it -> a;
		ssr.erase(it);

		if (r < pos)
			return ssr.emplace(pos, pos, vector <int> {0}).first;

		if (k <= 30)
		{
			for (auto &i : a) i >>= k;
			k = 0;
		}
		else
			return ssr.emplace(pos, pos, vector <int> {0}).first;

		/*
		for (int i = l, j; i <= pos - 1; i++) if (a[i - l])
		{
			int j = i;
			vector <int> A;
			while (j < pos - 1 && a[j + 1 - l]) j++;
			REP(k, i, j) A.emplace_back(a[k - l]);
			ssr.emplace(i, j, A);
			i = j;
		}
		IT res;bool flg = 0;
		for (int i = pos, j; i <= r; i++) if (a[i - l])
		{
			int j = i;
			vector <int> A;
			while (j < r && a[j + 1 - l]) j++;
			REP(k, i, j) A.emplace_back(a[k - l]);
			if (i == pos) res = ssr.emplace(i, j, A).first, flg = 1;
			i = j;
		}
		if (flg) return res;
		return ssr.emplace(pos, pos, vector <int> {0}).first;
		*/

		REP(i, l, pos - 1) a1.emplace_back(a[i - l]);
		REP(i, pos, r) a2.emplace_back(a[i - l]);

		int L = l, R = pos - 1;vector <int> real;
		while (L <= R && !a1[L - l]) L++;
		while (L <= R && !a1.back()) a1.pop_back(), R--;
		REP(i, L, R) real.emplace_back(a1[i - l]);
		if (L <= R) ssr.emplace(L, R, real, k);

		L = pos;R = r;real.clear();
		while (L <= R && !a2[L - pos]) L++;
		while (L <= R && !a2.back()) a2.pop_back(), R--;
		REP(i, L, R) real.emplace_back(a2[i - l]);
		if (L <= pos && pos <= R) return ssr.emplace(L, R, real, k).first;
		else
		{
			if (L <= R) ssr.emplace(L, R, real);
			return ssr.emplace(pos, pos, vector <int> {0}).first;
		}
	}
	void rebuild_a()
	{
		REP(i, 1, n) a[i] = 0;
		for (auto i : ssr)
			REP(j, i.l, i.r) a[j] = i.k <= 30 ? i.a[j - i.l] >> i.k : 0;
	}
	void rebuild_s()
	{
		ssr.clear();
		REP(i, 1, blg[n])
		{
			vector <int> A;
			int flg = 0;
			REP(j, L[i], R[i]) A.emplace_back(a[j]), flg |= a[j];
			if (!flg) continue;
			ssr.emplace(L[i], R[i], A);
		}
	}
	void rebuild()
	{
		rebuild_a();
		rebuild_s();
	}

	void work()
	{
		REP(i, 1, n) blg[i] = (i - 1) / b1 + 1;
		REP(i, 1, n) R[blg[i]] = i;
		DEP(i, n, 1) L[blg[i]] = i;

		rebuild_s();

		REP(Case, 1, q)
		{
			int opt = read<int>(), l = read<int>(), r = read<int>();
			if (opt == 1)
			{
				int x = read<int>();
				auto itr = split(r + 1), itl = split(l);
				vector <node> vec;
				for (auto it = itl; it != itr; it++) vec.emplace_back(*it);
				itr = split(x + r - l + 1), itl = split(x);
				ssr.erase(itl, itr);
				for (auto i : vec)
				{
					auto t = i;
					t.l += x - l;t.r += x - l;
					ssr.emplace(t);
				}
			}
			else if (opt == 2)
			{
				auto itr = split(r + 1), itl = split(l);
				for (auto it = itl; it != itr;)
				{
					it -> k++;
					if (it -> s.size() > 1)
					{
						it -> s.pop_back();
						it++;
					}else it = ssr.erase(it);
				}
			}
			else
			{
				i64 ans = 0;
				auto itr = split(r + 1), itl = split(l);
				for (auto it = itl; it != itr; it++) ans += it -> s.back();
				printf("%lld\n", ans);
			}
			if (ssr.size() > b2) rebuild();
			if (Case % 5000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", Case, q, Case * 100. / q);
		}
	}
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	q = read<int>();
	if (n <= 3e4 && q <= 3e4) bf :: work();
	else cheat :: work();
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
