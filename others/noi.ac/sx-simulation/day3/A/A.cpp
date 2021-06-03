/*
	Problem:	A.cpp
	Time:		2021-06-02 18:04
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q, m;

char s[maxn << 1], t[maxn];
namespace SAM
{
	const int maxn = (::maxn * 2) << 1;
	int ch[maxn][27], len[maxn], fail[maxn], lst = 1, cur = 1;
	void extend(int c)
	{
		int u = ++cur, v = lst;
		lst = u;
		len[u] = len[v] + 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
		else
		{
			int New(++cur), Old(ch[v][c]);
			copy(ch[Old], ch[Old] + 27, ch[New]);
			len[New] = len[v] + 1;
			fail[New] = fail[Old];
			fail[Old] = fail[u] = New;
			for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
		}
	}
	int pos[maxn], sa[maxn], lk, lc[maxn], rc[maxn];
	vector <pair <char, int> > G[maxn];
	void dfs(int x)
	{
		if (n - pos[x] + 1 == len[x]) sa[++lk] = pos[x], lc[x] = rc[x] = lk;
		else lc[x] = n + 1, rc[x] = 0;
		for (auto y : G[x])
		{
			dfs(y.second);
			lc[x] = min(lc[x], lc[y.second]);
			rc[x] = max(rc[x], rc[y.second]);
		}
	}
	void getsa()
	{
		scanf("%s", s + 1);n = strlen(s + 1);
		REP(i, 1, n) s[++n] = 'a' - 1;
		DEP(i, n, 1) extend(s[i] - ('a' - 1));
		int p = 1;
		DEP(i, n, 1)
		{
			p = ch[p][s[i] - ('a' - 1)];
			for (int x = p; x && !pos[x]; x = fail[x]) pos[x] = i;
		}
		REP(i, 2, cur)
			G[fail[i]].emplace_back(s[pos[i] + len[fail[i]]], i);
		REP(i, 1, cur) sort(G[i].begin(), G[i].end());
		dfs(1);
	}
}
using SAM :: sa;

inline bool cmp(char *t, int lt, int sf, int ard)
{
	REP(i, ard + 1, lt)
	{
		if (sf + i - 1 > n) return 0;
		if (t[i] < s[sf + i - 1]) return 1;
		if (t[i] > s[sf + i - 1]) return 0;
	}
	return 1;
}
inline bool same(char *t, int lt, int sf, int ard)
{
	REP(i, ard + 1, lt)
	{
		if (sf + i - 1 > n)			return 0;
		if (t[i] ^ s[sf + i - 1])	return 0;
	}
	return 1;
}
void get(char *t, int lt, int L, int R, int &l, int &r, int ard = 0)
{
	if (!lt) {l = L;r = R;return;}
	int tl = L, tr = R;
	
	l = R + 1;r = R;
	while (L <= R)
	{
		int mid = L + R >> 1;
		if (cmp(t, lt, sa[mid], ard))
		{
			l = mid;
			R = mid - 1;
		}
		else L = mid + 1;
	}	
	if (l == tr + 1) return;
	
	L = l;R = tr;r = l - 1;
	while (L <= R)
	{
		int mid = L + R >> 1;
		if (same(t, lt, sa[mid], ard))
		{
			r = mid;
			L = mid + 1;
		}
		else R = mid - 1;
	}
}
int rk[maxn << 1];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	SAM :: getsa();
	REP(i, 1, n) rk[sa[i]] = i;

#ifdef CraZYali
	REP(i, 1, n)
	{
		REP(j, sa[i], n) putchar(s[j]);
		puts("");
	}
	puts("");
#endif

	int q;cin >> q;
	while (q--)
	{
		scanf("%s", t + 1);m = strlen(t + 1);
		if (m > n / 2) {puts("0");continue;}
		i64 ans = 0;
		
		static int bl[maxn], br[maxn];
//		DEP(i, m, 1) get(t + i, m - i, 1, n, bl[i], br[i]);
		int p = 1;
		DEP(i, m, 1)
		{
			if (!p) bl[i] = n + 1, br[i] = n;
			else bl[i] = SAM :: lc[p], br[i] = SAM :: rc[p];
			p = SAM :: ch[p][t[i] - ('a' - 1)];
		}

		int l = 1, r = n;
		REP(i, 1, m)
		{
			if (l > r) break;
			int c = t[i];

			if (bl[i] <= br[i]) REP(orz, 'a', 'z') if (orz ^ c)
			{
				t[i] = orz;
				int L, R;
				get(t, i, l, r, L, R, i - 1);
				if (L > R) continue;
//				REP(j, L, R) if (bl[i] <= rk[sa[j] + i] && rk[sa[j] + i] <= br[i]) ans++;
				int tl = L, tr = R, rl = R + 1, rr = R;
				while (L <= R)
				{
					int mid = L + R >> 1;
					if (rk[sa[mid] + i] >= bl[i])
					{
						rl = mid;
						R = mid - 1;
					}
					else L = mid + 1;
				}
				if (rl == tr + 1) continue;
				rr = rl - 1;
				L = rl;R = tr;
				while (L <= R)
				{
					int mid = L + R >> 1;
					if (rk[sa[mid] + i] <= br[i])
					{
						rr = mid;
						L = mid + 1;
					}
					else R = mid - 1;
				}
				ans += rr - rl + 1;
//				get(t, m, L, R, L, R, i);
//				ans += max(R - L + 1, 0);
			}
			t[i] = c;
			get(t, i, l, r, l, r, i - 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
