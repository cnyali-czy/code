#define REP(i, s, e) for (register i64 i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register i64 i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;
#define i64 long long
#ifndef CraZYali
#define getchar getchar_unlocked
#endif
template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n;
i64 ans;
const i64 lim = (1ll << 62) - 1;

i64 l[maxn], r[maxn];
i64 query(int dep, i64 val, i64 L, i64 R, i64 cur)
{
	i64 l = cur, r = cur + ((unsigned i64)1 << dep + 1) - 1;
	if (r < L || l > R) return 0;
	if (L <= l && r <= R) return r;
	if (dep == -1) return 0;
	if (val >> dep & 1)	return	query(dep - 1, val, L, R, cur | (1ll << dep));
	else				return	query(dep - 1, val, L, R, cur) ||
								query(dep - 1, val, L, R, cur | (1ll << dep));
}
#include <map>

vector <pair <i64, i64> > vv;

bool ok(i64 val)
{
	REP(i, 1, n)
		if (!query(62, val, l[i], r[i], 0)) return 0;
	return 1;
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		l[i] = read<i64>();r[i] = read<i64>();
		vv.emplace_back(l[i], r[i]);
//		i64 l = read<i64>(), r = read<i64>();
//		insert(rt[i], 62, l, r);
	}
	sort(vv.begin(), vv.end());
	vv.resize(unique(vv.begin(), vv.end()) - vv.begin());
	n = 0;
	for (auto i : vv)
	{
		++n;
		l[n] = i.first;
		r[n] = i.second;
	}
	DEP(i, 62, 0) if (ok(ans | (1ll << i))) ans |= (1ll << i);
	cout << ans << endl;
	return 0;
}
