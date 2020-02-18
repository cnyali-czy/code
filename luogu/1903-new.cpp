/*
	Problem:	1903-new.cpp
	Time:		2020-02-18 15:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;
const int maxn = 133333 + 5, maxm = 133333 + 5;
inline char Getchar(){
    static char buf[200000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,200000,stdin),p1==p2)?EOF:*p1++;
}
template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = Getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = Getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = Getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, a[maxn], blg[maxn], block = 4096;

int C;
pair <int, int> change[maxm];

int q;
struct Query
{
	int l, r, t, id;
	inline bool operator < (const Query &B) const
	{
		if (blg[l] < blg[B.l]) return 1;
		if (blg[l] > blg[B.l]) return 0;
		if (blg[l] & 1)	return blg[r] < blg[B.r] || blg[r] == blg[B.r] && t < B.t;
		else			return blg[r] > blg[B.r] || blg[r] == blg[B.r] && t < B.t;
	}
}Q[maxm];

int cur, cnt[1000005], ans[maxm], l, r, t;
#define add(x) {cur += !cnt[x]++;}
#define del(x) {cur -= !--cnt[x];}
#define StandPower(t)\
{\
	int x = change[t].first, &y = change[t].second;\
	if (l <= x && x <= r) del(a[x]);\
	swap(a[x], y);\
	if (l <= x && x <= r) add(a[x]);\
}

inline void OutputTime()
{
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
}

int main()
{
#ifdef CraZYali
	file("1903-new");
#endif
	n = read<int>();m = read<int>();
	int ccc = block;
	REP(i, 1, n)
	{
		a[i] = read<int>();
		if (ccc == block) ccc = 0, blg[i] = blg[i-1] + 1;
		else blg[i] = blg[i-1];
		ccc++;
	}
	REP(i, 1, m)
	{
		char c = Getchar();
		while (!isalpha(c)) c = Getchar();
		int x = read<int>(), y = read<int>();
		if (c == 'Q') {++q;Q[q] = Query{x, y, C, q};}
		else change[++C] = make_pair(x, y);
	}
	OutputTime();
	sort(Q + 1, Q + 1 + q);
	REP(i, 1, q)
	{
		while (l > Q[i].l) add(a[--l]);
		while (r < Q[i].r) add(a[++r]);
		while (l < Q[i].l) del(a[l++]);
		while (r > Q[i].r) del(a[r--]);
		while (t < Q[i].t) {++t;StandPower(t);}
		while (t > Q[i].t) {StandPower(t);t--;}
		ans[Q[i].id] = cur;
	}
	REP(i, 1, q) cout << ans[i] << '\n';
	OutputTime();
	return 0;
}
