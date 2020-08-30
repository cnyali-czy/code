/*
	Problem:	3865-new.cpp
	Time:		2020-08-17 15:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

inline void chkmax(int &x, int y) {if (x < y) x = y;}

using namespace std;
const int maxn = 1e5 + 10;

struct IO {
#define MAXSIZE (1 << 20)
	char buf[MAXSIZE], *p1, *p2;
	char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
	inline char gc() {
#if DEBUG  // 调试，可显示字符
		return getchar();
#endif
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}
	inline int read()
	{
		register int ans = 0;
		register char c = gc();
		while (!isdigit(c)) c = gc();
		while (isdigit(c)) ans = ans * 10 + c - 48, c = gc();
		return ans;
	}
	inline void push(const char &c) {
#if DEBUG  // 调试，可显示字符
		putchar(c);
#else
		if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
		*pp++ = c;
#endif
	}
	template <class T>
		inline void write(T x) {
			static T sta[35];
			T top = 0;
			do {
				sta[top++] = x % 10, x /= 10;
			} while (x);
			while (top) push(sta[--top] + '0');
		}
	template <class T>
		inline void write(T x, char lastChar) {
			write(x), push(lastChar);
		}
} io;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
//inline int max(int x, int y) {return x > y ? x : y;}
int lg[maxn];
struct ST
{
	int m[6000][14];
	void init(int a[], int n)
	{
		REP(i, 1, n) m[i][0] = a[i];
		REP(j, 1, 13)
			REP(i, 1, n - (1 << j) + 1)
			m[i][j] = max(m[i][j - 1], m[i + (1 << j - 1)][j - 1]);
	}
	int query(int l, int r)
	{
		int k = lg[r - l + 1];
		return max(m[l][k], m[r - (1 << k) + 1][k]);
	}
}orzjjs;
int a[maxn], n, q;

namespace divide
{
	int mx[maxn], mp[maxn], ms[maxn], N, block;
	void init()
	{
		block = lg[n] + 1;
		N = (n - 1) / block + 1;
		for (int L = 1, R = block, i = 1; L <= n; L += block, R += block, i++)
		{
			if (R > n) R = n;
			REP(j, L, R) chkmax(mx[i], a[j]);
			mp[L] = a[L];
			REP(j, L + 1, R)
				mp[j] = max(mp[j - 1], a[j]);
			ms[R] = a[R];
			DEP(j, R - 1, L)
				ms[j] = max(ms[j + 1], a[j]);
		}
		orzjjs.init(mx, N);
	}
	int query(int l, int r)
	{
		int bl = (l - 1) / block + 1, br = (r - 1) / block + 1;
		if (bl == br)
		{
			int ans = a[l];
			REP(i, l + 1, r) chkmax(ans, a[i]);
			return ans;
		}
		else return max(max(ms[l], mp[r]), bl + 1 < br ? orzjjs.query(bl + 1, br - 1) : 0);
	}
}

int main()
{
#ifdef CraZYali
	file("3865-new");
#endif
	n = io.read();q = io.read();
	REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	REP(i, 1, n) a[i] = io.read();
	divide :: init();

	while (q--)
	{
		int l(io.read()), r(io.read());
		io.write(divide :: query(l, r), '\n');
	}
	return 0;
	xzxcsscccccccccxx      cccxxxzzzzaasdqwesdqwaqweddaqlddslldsdslkdslklksdlfgkoldkoleodcxlkcvoiklgfkoltriotgyoiklgtyikoghkiolytgtgtgtgtgtgtgtgikgkihjlkgfgfgffasfd;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;al;jkklasdf;jlsadkfj;dasdfkl;jlk;jasdffasd;jklfsdjkla;ajfklsd;sdjklaf;l;kjadfsclk;awdfjscsdflk;jljkfsd;pwefuasdpoij ¬ëîéí                                                   mkjio9njhhnjgbjnhgfmâîâíæãö   vbmmvb    vbm, vbm,,,,,,,,,,,,,,,,,,înnnnnnnnnnn<F5><F6><F8><F7>ioukjlgf âî¬öéçï¹°ðæ íîö¬¹éïôù°¸ç ¬íî®ëæêl hyu8ikjuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuunnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnbvcxxxxxxxxxxxxbiiiic 9<F10>
