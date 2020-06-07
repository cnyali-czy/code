#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
 
#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)
 
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
const int MOD = 998244353, maxn = 1e6 + 10, inv2 = MOD + 1 >> 1, inv3 = (MOD + 1) / 3, inv6 = 1ll * inv2 * inv3 % MOD ;
 
inline void inc(int &x, int y) {x += y; if (x >= MOD) x -= MOD;}
 
#define i64 long long
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
 
int m, n, k;
string Case;
int l[maxn], r[maxn], lg[maxn];
 
struct table
{
    int pos[maxn][21], flag, a[maxn];
    //flag = 0 : Max
    //flag = 1 : Min
    void init()
    {
		REP(i, 1, n) pos[i][0] = i;
		DEP(i, n, 1)
			REP(j, 1, 20) if (i + (1 << j) - 1 <= n)
			{
				int x = a[pos[i][j - 1]], y = a[pos[i + (1 << j - 1)][j - 1]];
				int res = flag ? min(x, y) : max(x, y);
				if (res == x)   pos[i][j] = pos[i][j - 1];
				else            pos[i][j] = pos[i + (1 << j - 1)][j - 1];
			}
		else break;
	}
	int query(int l, int r)
	{
		int k = lg[r - l + 1];
		int X = pos[l][k], Y = pos[r - (1 << k) + 1][k];
		int x = a[X], y = a[Y];
		return flag ? min(x, y) : max(x, y);
	}
	int query_pos(int l, int r)
	{
		int k = lg[r - l + 1];
		int X = pos[l][k], Y = pos[r - (1 << k) + 1][k];
		int x = a[X], y = a[Y];
		int res = flag ? min(x, y) : max(x, y);
		if (res == x)   return pos[l][k];
		else            return pos[r - (1 << k) + 1][k];
	}
}cur;
int len[maxn], leni[maxn];
inline int s1(int n) {n %= MOD;return n < 1 ? 0 : n * (n + 1ll) / 2 % MOD;}
inline int s2(int n) {n %= MOD;return n < 1 ? 0 : n * (n + 1ll) / 2 % MOD * (n + n + 1ll) % MOD * inv3 % MOD;}
inline int s1(int l, int r) {return (MOD + (i64)s1(r) - s1(l - 1)) % MOD;}
inline int s2(int l, int r) {return (MOD + (i64)s2(r) - s2(l - 1)) % MOD;}
inline int sn(int n) {return 1ll * (s2(n) + s1(n)) * inv2 % MOD;}
int s[maxn], ss[maxn], su[maxn];
//int gx[4][10][10][10][10], qaq;
i64 Div(int a[], int l, int r, int lim)
{
	if (l > r) return 0;
	int pos = cur.query_pos(l, r), M = a[pos];
	//	if(lim > M) return 0;
	i64 res = 0;
	/* wrong
	   (res += (r - l + 1ll) * (M - lim + 1ll) % MOD * (ss[r] - ss[l - 1] + s[r] - s[l])) %= MOD;
	   (res += (r - l + 1ll) * s1(lim, M) % MOD * (s[r] - s[l - 1])) %= MOD;
	   (res += (r - l + 1ll) * (r - l + 2ll) / 2 % MOD * (s2(lim, M) - s1(lim, M))) %= MOD;
	   if (res < 0) res += MOD;
	   */
	/*
	 * wrong
	 (res += (M - lim + 1ll) * (su[r] - su[l - 1])) %= MOD;
	 (res -= (M - lim + 1ll) * (r - l + 1) % MOD * s1(lim)) %= MOD;
	 (res -= (su[r] - su[l - 1] - (r - l + 1ll) * (lim - 1)) % MOD * (s1(M) - s1(lim - 1))) %= MOD;
	 */
	/* right
	   REP(j, lim, M)
	   {
	   (res += ( s[r] - s[l - 1] - (r - l + 1ll) * s1(j - 1) % MOD - 1ll * j * (su[r] - su[l - 1]) % MOD + (1ll * j * j - j) % MOD * (r - l + 1) % MOD  )) %= MOD;
	   }
	   */
	res = (M - lim + 1ll) * (s[r] - s[l - 1]) % MOD - (r - l + 1ll) * (sn(M - 1) - (lim >= 2 ? sn(lim - 2) : 0)) % MOD - 1ll * s1(lim, M) * (su[r] - su[l - 1]) % MOD + (r - l + 1ll) * (s2(lim, M) - s1(lim, M)) % MOD;
	/* right
	   REP(j, lim, M)
	   REP(ii, l, r) REP(jj, j, a[ii])
	   {
	   (res += jj - j) %= MOD;
	   }
	   */
	res %= MOD;
	(res *= r - l + 1) %= MOD;
	if (res < 0) res += MOD;
	//	cout << l << ' '<< r << ' ' << lim << ' ' << M << ' ' << pos << ' ' << res << endl;
	i64 res2 = 0;
	if (l < pos && pos < r)
	{
		i64 ss1 = (su[pos - 1] - su[l - 1]) - 1ll * M * (pos - l) % MOD;
		i64 ss2 = (su[r] - su[pos]) - 1ll * M * ( r  -  pos ) % MOD;
		(res2 -= 2ll * M * ss1 % MOD * ss2 % MOD) %= MOD;
		/*
		   int cnt = 0;
		   REP(i, l, pos - 1) REP(j, pos + 1, r)
		   REP(x, M + 1, a[i]) REP(y, M + 1, a[j]) (res2 +=  - M - M ) %= MOD, cnt++;
		   cout << cnt << " = " << ss1 * ss2 % MOD << endl;
		   */
	} 
	//  REP(i, l, pos - 1)
	//  {
	//      REP(x, M + 1, a[i])
	i64 tmp = (s[pos - 1] - s[l - 1] - 1ll * s1(M) * (pos - l) % MOD) % MOD;
	(res2 += 1ll * (su[r] - su[pos]) * tmp % MOD - 1ll * M * tmp % MOD * (r - pos)) %= MOD;
	tmp = (s[r] - s[pos] - 1ll * s1(M) * (r - pos) % MOD) % MOD;
	(res2 += 1ll * (su[pos] - su[l - 1]) * tmp % MOD - 1ll * M * tmp % MOD * (pos - l + 1)) %= MOD;
	//          (res2 += 1ll * (su[r] - su[pos]) * s1(M + 1, a[i]) - 1ll * M * s1(M + 1, a[i]) % MOD * (r - pos)) %= MOD;
	//          REP(j, pos + 1, r) (res2 += 1ll * (a[j] - M) * x) %= MOD;
	//  }
	//  cout << l << ' '<< r << ' ' << lim << ' ' << M << ' ' << pos << ' ' << res2 << endl;
	res += res2;
	return (res + Div(a, l, pos - 1, M + 1) + Div(a, pos + 1, r, M + 1)) % MOD;
}

i64 solve(int a[], int n, int flag)
{
	//  if (flag == -1) qaq = 2;
	//  else qaq = 3;
	REP(i, 1, n) a[i] *= flag;
	REP(i, 1, n)
	{
		//		sn[i] = s1(i);      inc(sn[i], sn[i - 1]);
		su[i] = a[i];       inc(su[i], su[i - 1]);
		s[i] = s1(a[i]);    inc(s[i], s[i - 1]);
		ss[i] = s2(a[i]);   inc(ss[i], ss[i - 1]);
	}
	REP(i, 1, n) cur.a[i] = a[i];
	cur.flag = 1;
	cur.init();
	return Div(a, 1, n, 1);
}


signed main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> Case;
	REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	REP(i, 1, n)
	{
		l[i] = read<int>();
		r[i] = read<int>() - 1;
		len[i] = (r[i] - l[i] + 1) % MOD;
		leni[i] = 1ll * len[i] * i % MOD;
	}
	i64 ans = 0;
	DEP(i, n, 1)
	{
		ans += (leni[i + 1] - 1ll * i * len[i + 1]) % MOD * len[i] % MOD;
		inc(len[i], len[i + 1]);
		inc(leni[i], leni[i + 1]);
	}
	ans = ans * 2ll % MOD;
	if (ans < 0) ans += MOD;
	REP(i, 1, n)
		ans += 2ll * n * (s1(r[i]) + s1(-l[i])) % MOD;
	ans %= MOD;
	i64 sl = 0, sr = 0;
	REP(i, 1, n) sl -= l[i], sr += r[i];
	// sl = - sigma l[i]
	sl = (sl % MOD + MOD) % MOD;
	sr %= MOD;
	REP(i, 1, n)
		ans += 2 * (s1(r[i]) * sl + s1(-l[i]) * sr) % MOD;
	ans %= MOD;
	//  REP(i, 1, n) REP(j, i, n) printf("%d %d %d %d\n", i, j, L.query(i, j), R.query(i, j));
	i64 res1 = 0, res2 = 0;
	/*
	   REP(i, 1, n) REP(j, 1, n)
	   REP(x, l[i], r[i]) REP(y, l[j], r[j])
	   {
	   if (!x || !y) continue;
	   int I = i, J = j;
	   if (I > J) swap(I, J);
	//ans += J - I;
	//          if (x < 0 && y > 0) ans += y - x;
	//          if (x > 0 && y < 0) ans += x - y;
	if (x < 0 && y < 0)
	{
	i64 rit = l[I];
	REP(k, I + 1, J) chkmax(rit, l[k]);
	if (rit > max(x, y)) res1 += rit * 2 - x - y;
	else                    res1 += abs(x - y);//, gx[0][i][-x][j][-y] = abs(x - y);
	}
	if (x > 0 && y > 0)
	{
	i64 lft = r[I];
	REP(k, I + 1, J) chkmin(lft, r[k]);
	if (lft < min(x, y)) res2 += x + y - lft * 2;
	else                    res2 += abs(x - y);//, gx[1][i][x][j][y] = abs(x - y);
	}
	}
	*/
	i64 tmp;
	tmp = solve(l, n, -1) * 2 % MOD;
#ifdef CraZYali
	cout << tmp << ' ' << res1 << endl;
#endif
	ans += tmp;
	//  puts("");
	tmp = solve(r, n, 1) * 2 % MOD;
#ifdef CraZYali
	cout << tmp << ' ' << res2 << endl;
#endif
	ans += tmp;
	/*
	   puts("");
	   REP(I, 0, 1)
	   {
	   REP(i, 0, 9) REP(j, 0, 9) REP(x, 0, 9) REP(y, 0, 9) if (gx[I][i][j][x][y] + gx[I + 2][i][j][x][y])
	   {
	   int qqq, qqqq;
	   qqq = gx[I][i][j][x][y], qqqq = gx[I + 2][i][j][x][y];
	   if (qqq ^ qqqq) DEBUG,printf("%d %d : GG %d %d %d %d %d\n", qqq,qqqq,I, i, j, x, y);
	   }
	   puts("");
	   }
	   */

	cout << ans % MOD << endl;
	return 0;
}
