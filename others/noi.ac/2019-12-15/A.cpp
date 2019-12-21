/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2019.12.15 09:08
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 8e6 + 5;
template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

char s[maxn];
int n, q;
const int B = 4000 + 5, tot = maxn / B;
int S[13][tot + 5];
inline void add(int c[], int x, char val)
{
	while (x < tot + 5)
	{
		c[x] += val;
		x += x & -x;
	}
}
inline int sum(int c[], int x)
{
	int res(0);
	while (x > 0)
	{
		res += c[x];
		x -= x & -x;
	}
	return res;
}
inline int sum(int c[], int l, int r)
{
	return sum(c, r) - sum(c, l - 1);
}
inline int nxt(int x) {return x == 12 ? 1 : x + 1;}
int dp[13], tmp[13];
int L(int x) {return (x - 1) * B + 1;}
int R(int x) {return x * B;}
int blg(int x) {return (x - 1) / B + 1;}
int Count[13];
inline void work(int i, int tot)
{
	for (int j = 1; j <= tot; j <<= 1)//++)// <<= 1)
	{
		tot -= j;
		REP(I, 0, 12) tmp[I] = dp[I];
		REP(I, 0, 12) tmp[(I + 1ll * i * j % 13) % 13] += dp[I];
		REP(I, 0, 12) dp[I] = tmp[I];
	}
	if (tot) work(i, tot);
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> q;
	scanf("%s", s + 1);
	REP(i, 1, n)
		if (!isdigit(s[i])) s[i] = s[i] - 'a' + 10;
		else s[i] = s[i] - '0';
	REP(i, 1, n) add(S[s[i]], blg(i), 1);//[blg(i)]++;
	while (q--)
	{
		int l(read<int>()), r(read<int>());
		dp[0] = 1;
		REP(i, 1, 12) dp[i] = 0, Count[i] = 0;
		int bl(blg(l)), br(blg(r)), Lbl(L(bl)), Lbr(L(br));
		if (bl == br)
			REP(i, l, r) Count[s[i]]++;
		else
		{
			REP(j, l, R(bl)) Count[s[j]]++;
			REP(j, L(br), r) Count[s[j]]++;
			REP(i, 1, 12)
				Count[i] += sum(S[i], bl + 1, br - 1);
//				REP(j, bl + 1, br - 1)
//				Count[i] += S[i][j];
		}
		REP(i, 1, 12)
			work(i, Count[i]);
		REP(i, 0, 12) putchar((1 & dp[i]) + 48);putchar(10);
		add(S[s[l]], blg(l), -1);
		add(S[s[l] = nxt(s[l])], blg(l), 1);
		add(S[s[r]], blg(r), -1);
		add(S[s[r] = nxt(s[r])], blg(r), 1);
	}
	return 0;
}
