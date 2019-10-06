#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define cREP(i, s, e) for (register char i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 10, maxk = 500 + 10;

inline char Getchar()
{
    static char buf[100000],*p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read()
{
	register T ans(0);
	register char c(Getchar());
	while (!isdigit(c)) c = Getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = Getchar();
	}
	return ans;
}

int n, k[maxn];
long long Ans;
int bit[1<<20];

struct bitset
{
	unsigned int s[16];
	inline bitset() {cREP(i, 0, 15) s[i] = 0;}
	inline void set(int x)
	{
		s[x >> 5] |= 1 << (x & 31);
	}
	inline int count()
	{
		register int ans(0);
		cREP(i, 0, 15) ans += bit[s[i] >> 16] + bit[s[i] & 65535];
		return ans;
	}
};

bitset ans;
inline bitset operator & (const bitset &A, const bitset &B) 
{
	cREP(i, 0, 15) ans.s[i] = A.s[i] & B.s[i];
	return ans;
}
inline bitset operator | (const bitset &A, const bitset &B) 
{
	cREP(i, 0, 15) ans.s[i] = A.s[i] | B.s[i];
	return ans;
}
inline bitset operator ^ (const bitset &A, const bitset &B) 
{
	cREP(i, 0, 15) ans.s[i] = A.s[i] ^ B.s[i];
	return ans;
}
inline bitset operator ^= (bitset &A, const bitset &B) {return A = A ^ B;}
inline bitset operator |= (bitset &A, const bitset &B) {return A = A | B;}
inline bitset operator ~ (const bitset &A) 
{
	cREP(i, 0, 15) ans.s[i] = ~A.s[i];
	return ans;
}
inline bitset operator + (const bitset &A, const bitset &B) 
{
	register unsigned w(0);
	cREP(i, 0, 15)
	{
		register long long t = 1ll * A.s[i] + B.s[i] + w;
		ans.s[i] = t & ((1ll << 32) - 1);
		w = t >> 32;
	}
	return ans;
}

bitset x, y, t, S[maxn];

int main()
{
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	REP(i, 1, 1 << 17)
		bit[i] = bit[i >> 1] + (i & 1);
	REP(i, 1, n = read<int>())
		REP(j, 1, k[i] = read<int>()) S[i].set(read<int>() - 1);
	REP(i, 1, n)
		REP(j, i + 1, n)
		{
			x = S[i];
			y = S[j];
			t = x & y;
			Ans ^= 1ll * i * j * (t | (y & ((x ^ t) + (~y)))).count();
		}
	cout << Ans << endl;
	return 0;
}
