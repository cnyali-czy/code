/*
	Problem:	3793.cpp
	Time:		2020-10-27 23:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#include <ctime>

inline void chkmax(int &x, int y) {if (x < y) x = y;}

using namespace std;
const int maxn = 2e7 + 10;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
int lg_table[1 << 13];
inline int lg(int x)
{
	if (x < 8192) return lg_table[x & 8191];
	return 13 + lg_table[x >> 13];
}

namespace ST
{
	int m[15][19600];
	void init(int a[], int n)
	{
		REP(i, 1, n) m[0][i] = a[i];
		REP(j, 1, lg(n))
			REP(i, 1, n - (1 << j) + 1)
			m[j][i] = max(m[j - 1][i], m[j - 1][i + (1 << j - 1)]);
	}
	inline int query(int l, int r)
	{
		int k = lg(r - l + 1);
		return max(m[k][l], m[k][r - (1 << k) + 1]);
	}
}
int a[maxn], n, q;
unsigned s;

namespace divide
{
	int mx[maxn], mp[maxn], ms[maxn], N, block;
	int blg[maxn];
	void init()
	{
		block = 1024;
		N = (n - 1) / block + 1;
		for (int L = 1, R = block, i = 1; L <= n; L += block, R += block, i++)
		{
			if (R > n) R = n;
			mp[L] = a[L];
			REP(j, L + 1, R) mp[j] = max(mp[j - 1], a[j]);
			mx[i] = mp[R];
			ms[R] = a[R];
			DEP(j, R - 1, L) ms[j] = max(ms[j + 1], a[j]);
		}
		ST :: init(mx, N);
	}
	inline int query(int l, int r)
	{
		const static int block = divide :: block;
		int bl = (l - 1) / block + 1, br = (r - 1) / block + 1;
		if (bl == br)
		{
			int ans = a[l];
			REP(i, l + 1, r) chkmax(ans, a[i]);
			return ans;
		}
		int res = max(ms[l], mp[r]);
		if (bl + 1 < br) chkmax(res, ST :: query(bl + 1, br - 1));
		return res;
	}
}

namespace GenHelper
{
    unsigned z1,z2,z3,z4,b;
    inline unsigned rand_()
    {
    b=((z1<<6)^z1)>>13;
    z1=((z1&4294967294U)<<18)^b;
    b=((z2<<2)^z2)>>27;
    z2=((z2&4294967288U)<<2)^b;
    b=((z3<<13)^z3)>>21;
    z3=((z3&4294967280U)<<7)^b;
    b=((z4<<3)^z4)>>12;
    z4=((z4&4294967168U)<<13)^b;
    return (z1^z2^z3^z4);
    }
}
void srand(unsigned x)
{using namespace GenHelper;
z1=x; z2=(~x)^0x233333333U; z3=x^0x1234598766U; z4=(~x)+51;}
inline int read()
{
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}

int main()
{
#ifdef CraZYali
	file("3793");
#endif
	cin >> n >> q >> s;
	srand(s);
	REP(i, 2, (1 << 13) - 1) lg_table[i] = lg_table[i >> 1] + 1;
	REP(i, 1, n) a[i] = read();
	divide :: init();
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	const int N = n;
	unsigned long long ans = 0;
	
	while (q--)
	{
		int l = read() % N + 1, r = read() % N + 1;
		if (l > r) swap(l, r);
		ans += divide :: query(l, r);
	}
	cout << ans << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
