#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 1e5 + 10;

inline char Getchar()
{
    static char buf[100000],*p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read()
{
	T ans(0);
	char c(Getchar());
	while (!isdigit(c)) c = Getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = Getchar();
	}
	return ans;
}

int n, k;
pair <int, int> a[maxn];

multiset <int> S;
inline bool cmp (const pair <int, int> &A, const pair <int, int> &B) {return A.second < B.second || A.second == B.second && A.first < B.first;}

int main()
{
#ifdef CraZYali
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	n = read<int>();
	k = read<int>();
	REP(i, 1, n)
	{
		register int l(read<int>()), r(read<int>());
		a[i] = make_pair(l, r);
	}
	sort(a + 1, a + 1 + n, cmp);
	REP(i, 1, k) S.insert(0);

	register int ans(0);
	REP(i, 1, n)
	{
		register auto it = S.upper_bound(a[i].first);
		if (it == S.begin()) continue;
		ans++;
		S.erase(--it);
		S.insert(a[i].second);
	}
	cout << ans << endl;
	return 0; 
}
