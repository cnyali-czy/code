/*
	Problem:	F.cpp
	Time:		2021-03-30 09:57
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <unordered_map>
#include <queue>
#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 long long

using namespace std;
const int MOD = 1e9 + 7;

inline i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, k, m;

int table[80][80][80];

namespace lag
{
	const int fk = 24;
	int y[50], L, R;
	/*
	int id[1 << fk];
	int f[fk][10000005];
//	unordered_map <int, int> f[fk];
	queue <pair <int, int> > que;
	inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
	
	void init()
	{
		
		int cur = 0;
		REP(i, 1, (1 << R) - 1) if (__builtin_popcount(i) <= k)
			id[i] = ++cur;

		REP(i, 1, R)
		{
			que.emplace(1 << i - 1, i - 1);
			f[i - 1][id[1 << i - 1]] = 1;
		}
		while (que.size())
		{
			auto Node = que.front();que.pop();
			int lst = Node.second, S = Node.first, v = f[lst][id[S]], pcnt = __builtin_popcount(S);
			if (pcnt == k)
			{
				int mx = 0;
				DEP(i, R, 0) if (S >> (i - 1) & 1) {mx = i;break;}
				inc(y[mx], v);
				continue;
			}
			REP(i, 1, min(lst + 1 + m, R)) if (!(S >> (i - 1) & 1))
			{
				int newS = S | (1 << i - 1);
				if (!f[i - 1][id[newS]]) que.emplace(newS, i - 1);
				inc(f[i - 1][id[newS]], v);
			}
		}
		REP(i, max(L, 1), R) inc(y[i], y[i - 1]);
		*/
	void init()
	{
		L = k;R = k + k;
		REP(i, L, R) y[i] = table[k][m][i];
	}
	int query(int n)
	{

		if (n < k) return 0;
		if (n <= R) return y[n];
		i64 ans = 0;
		REP(i, L, R)
		{
			i64 res = 1;
			REP(j, L, R) if (i ^ j)
				res = res * (n - j) % MOD * inv(i - j) % MOD;
			(ans += res * y[i]) %= MOD;
		}
		ans = (ans % MOD + MOD) % MOD;
		return ans;
	}
}

int main()
{
#ifdef CraZYali
	file("F");
#endif
table[1][1][1] = 1;
table[1][1][2] = 2;
table[1][2][1] = 1;
table[1][2][2] = 2;
table[1][3][1] = 1;
table[1][3][2] = 2;
table[1][4][1] = 1;
table[1][4][2] = 2;
table[2][1][2] = 2;
table[2][1][3] = 5;
table[2][1][4] = 9;
table[2][2][2] = 2;
table[2][2][3] = 6;
table[2][2][4] = 11;
table[2][3][2] = 2;
table[2][3][3] = 6;
table[2][3][4] = 12;
table[2][4][2] = 2;
table[2][4][3] = 6;
table[2][4][4] = 12;
table[3][1][3] = 4;
table[3][1][4] = 12;
table[3][1][5] = 25;
table[3][1][6] = 44;
table[3][2][3] = 6;
table[3][2][4] = 20;
table[3][2][5] = 42;
table[3][2][6] = 72;
table[3][3][3] = 6;
table[3][3][4] = 24;
table[3][3][5] = 54;
table[3][3][6] = 96;
table[3][4][3] = 6;
table[3][4][4] = 24;
table[3][4][5] = 60;
table[3][4][6] = 112;
table[4][1][4] = 8;
table[4][1][5] = 28;
table[4][1][6] = 66;
table[4][1][7] = 129;
table[4][1][8] = 225;
table[4][2][4] = 18;
table[4][2][5] = 68;
table[4][2][6] = 158;
table[4][2][7] = 296;
table[4][2][8] = 492;
table[4][3][4] = 24;
table[4][3][5] = 102;
table[4][3][6] = 254;
table[4][3][7] = 494;
table[4][3][8] = 830;
table[4][4][4] = 24;
table[4][4][5] = 120;
table[4][4][6] = 324;
table[4][4][7] = 662;
table[4][4][8] = 1154;
table[5][1][5] = 16;
table[5][1][6] = 64;
table[5][1][7] = 168;
table[5][1][8] = 360;
table[5][1][9] = 681;
table[5][1][10] = 1182;
table[5][2][5] = 54;
table[5][2][6] = 228;
table[5][2][7] = 582;
table[5][2][8] = 1180;
table[5][2][9] = 2100;
table[5][2][10] = 3436;
table[5][3][5] = 96;
table[5][3][6] = 444;
table[5][3][7] = 1206;
table[5][3][8] = 2520;
table[5][3][9] = 4518;
table[5][3][10] = 7340;
table[5][4][5] = 120;
table[5][4][6] = 624;
table[5][4][7] = 1818;
table[5][4][8] = 4008;
table[5][4][9] = 7470;
table[5][4][10] = 12420;
table[6][1][6] = 32;
table[6][1][7] = 144;
table[6][1][8] = 416;
table[6][1][9] = 968;
table[6][1][10] = 1970;
table[6][1][11] = 3653;
table[6][1][12] = 6321;
table[6][2][6] = 162;
table[6][2][7] = 756;
table[6][2][8] = 2102;
table[6][2][9] = 4584;
table[6][2][10] = 8688;
table[6][2][11] = 15028;
table[6][2][12] = 24362;
table[6][3][6] = 384;
table[6][3][7] = 1938;
table[6][3][8] = 5670;
table[6][3][9] = 12672;
table[6][3][10] = 24110;
table[6][3][11] = 41268;
table[6][3][12] = 65642;
table[6][4][6] = 600;
table[6][4][7] = 3312;
table[6][4][8] = 10362;
table[6][4][9] = 24390;
table[6][4][10] = 48060;
table[6][4][11] = 84120;
table[6][4][12] = 135422;
table[7][1][7] = 64;
table[7][1][8] = 320;
table[7][1][9] = 1008;
table[7][1][10] = 2528;
table[7][1][11] = 5500;
table[7][1][12] = 10836;
table[7][1][13] = 19825;
table[7][1][14] = 34232;
table[7][2][7] = 486;
table[7][2][8] = 2484;
table[7][2][9] = 7470;
table[7][2][10] = 17428;
table[7][2][11] = 35028;
table[7][2][12] = 63820;
table[7][2][13] = 108418;
table[7][2][14] = 174692;
table[7][3][7] = 1536;
table[7][3][8] = 8400;
table[7][3][9] = 26370;
table[7][3][10] = 62748;
table[7][3][11] = 126174;
table[7][3][12] = 226872;
table[7][3][13] = 377098;
table[7][3][14] = 591636;
table[7][4][7] = 3000;
table[7][4][8] = 17712;
table[7][4][9] = 59160;
table[7][4][10] = 147360;
table[7][4][11] = 306030;
table[7][4][12] = 561864;
table[7][4][13] = 944310;
table[7][4][14] = 1486020;
table[8][1][8] = 128;
table[8][1][9] = 704;
table[8][1][10] = 2400;
table[8][1][11] = 6448;
table[8][1][12] = 14920;
table[8][1][13] = 31092;
table[8][1][14] = 59906;
table[8][1][15] = 108545;
table[8][1][16] = 187137;
table[8][2][8] = 1458;
table[8][2][9] = 8100;
table[8][2][10] = 26190;
table[8][2][11] = 65072;
table[8][2][12] = 138192;
table[8][2][13] = 264404;
table[8][2][14] = 469442;
table[8][2][15] = 787584;
table[8][2][16] = 1263566;
table[8][3][8] = 6144;
table[8][3][9] = 36192;
table[8][3][10] = 121374;
table[8][3][11] = 306252;
table[8][3][12] = 648876;
table[8][3][13] = 1222524;
table[8][3][14] = 2118956;
table[8][3][15] = 3452742;
table[8][3][16] = 5365942;
table[8][4][8] = 15000;
table[8][4][9] = 94704;
table[8][4][10] = 335544;
table[8][4][11] = 882384;
table[8][4][12] = 1925652;
table[8][4][13] = 3697884;
table[8][4][14] = 6472746;
table[8][4][15] = 10570440;
table[8][4][16] = 16364988;
table[9][1][9] = 256;
table[9][1][10] = 1536;
table[9][1][11] = 5632;
table[9][1][12] = 16128;
table[9][1][13] = 39520;
table[9][1][14] = 86784;
table[9][1][15] = 175504;
table[9][1][16] = 332688;
table[9][1][17] = 598417;
table[9][1][18] = 1030490;
table[9][2][9] = 4374;
table[9][2][10] = 26244;
table[9][2][11] = 90774;
table[9][2][12] = 239244;
table[9][2][13] = 535172;
table[9][2][14] = 1072492;
table[9][2][15] = 1985610;
table[9][2][16] = 3461500;
table[9][2][17] = 5754206;
table[9][2][18] = 9202136;
table[9][3][9] = 24576;
table[9][3][10] = 155136;
table[9][3][11] = 553446;
table[9][3][12] = 1475856;
table[9][3][13] = 3285840;
table[9][3][14] = 6472260;
table[9][3][15] = 11676924;
table[9][3][16] = 19730940;
table[9][3][17] = 31698198;
table[9][3][18] = 48924852;
table[9][4][9] = 75000;
table[9][4][10] = 504240;
table[9][4][11] = 1890360;
table[9][4][12] = 5234352;
table[9][4][13] = 11972046;
table[9][4][14] = 23991264;
table[9][4][15] = 43661256;
table[9][4][16] = 73882716;
table[9][4][17] = 118165590;
table[9][4][18] = 180736056;
table[10][1][10] = 512;
table[10][1][11] = 3328;
table[10][1][12] = 13056;
table[10][1][13] = 39680;
table[10][1][14] = 102592;
table[10][1][15] = 236640;
table[10][1][16] = 500864;
table[10][1][17] = 990736;
table[10][1][18] = 1854882;
table[10][1][19] = 3317445;
table[10][1][20] = 5707449;
table[10][2][10] = 13122;
table[10][2][11] = 84564;
table[10][2][12] = 311526;
table[10][2][13] = 867960;
table[10][2][14] = 2039504;
table[10][2][15] = 4271252;
table[10][2][16] = 8229802;
table[10][2][17] = 14881720;
table[10][2][18] = 25591502;
table[10][2][19] = 42242656;
table[10][2][20] = 67385872;
table[10][3][10] = 98304;
table[10][3][11] = 662016;
table[10][3][12] = 2503080;
table[10][3][13] = 7033176;
table[10][3][14] = 16413600;
table[10][3][15] = 33733854;
table[10][3][16] = 63246888;
table[10][3][17] = 110673822;
table[10][3][18] = 183580850;
table[10][3][19] = 291827630;
table[10][3][20] = 448090402;
table[10][4][10] = 375000;
table[10][4][11] = 2674800;
table[10][4][12] = 10581048;
table[10][4][13] = 30769968;
table[10][4][14] = 73589040;
table[10][4][15] = 153613056;
table[10][4][16] = 290201886;
table[10][4][17] = 508176840;
table[10][4][18] = 838712676;
table[10][4][19] = 320498737;
table[10][4][20] = 1142492;
table[11][1][11] = 1024;
table[11][1][12] = 7168;
table[11][1][13] = 29952;
table[11][1][14] = 96256;
table[11][1][15] = 261760;
table[11][1][16] = 632448;
table[11][1][17] = 1397536;
table[11][1][18] = 2878144;
table[11][1][19] = 5597172;
table[11][1][20] = 10377180;
table[11][1][21] = 18474633;
table[11][1][22] = 31760676;
table[11][2][11] = 39366;
table[11][2][12] = 271188;
table[11][2][13] = 1059966;
table[11][2][14] = 3112452;
table[11][2][15] = 7663764;
table[11][2][16] = 16738956;
table[11][2][17] = 33507794;
table[11][2][18] = 62753172;
table[11][2][19] = 111478766;
table[11][2][20] = 189686600;
table[11][2][21] = 311359992;
table[11][2][22] = 495692456;
table[11][3][11] = 393216;
table[11][3][12] = 2813952;
table[11][3][13] = 11239488;
table[11][3][14] = 33186312;
table[11][3][15] = 81003252;
table[11][3][16] = 173393748;
table[11][3][17] = 337337352;
table[11][3][18] = 610550436;
table[11][3][19] = 44579719;
table[11][3][20] = 708599077;
table[11][3][21] = 693984764;
table[11][3][22] = 119765024;
table[11][4][11] = 1875000;
table[11][4][12] = 14142000;
table[11][4][13] = 58870968;
table[11][4][14] = 179364528;
table[11][4][15] = 447671856;
table[11][4][16] = 971803680;
table[11][4][17] = 903100813;
table[11][4][18] = 444529887;
table[11][4][19] = 860752559;
table[11][4][20] = 490500189;
table[11][4][21] = 761679830;
table[11][4][22] = 209440126;
table[12][1][12] = 2048;
table[12][1][13] = 15360;
table[12][1][14] = 68096;
table[12][1][15] = 230656;
table[12][1][16] = 657920;
table[12][1][17] = 1661056;
table[12][1][18] = 3823680;
table[12][1][19] = 8182432;
table[12][1][20] = 16498632;
table[12][1][21] = 31655820;
table[12][1][22] = 58227906;
table[12][1][23] = 103274625;
table[12][1][24] = 177435297;
table[12][2][12] = 118098;
table[12][2][13] = 866052;
table[12][2][14] = 3579390;
table[12][2][15] = 11047104;
table[12][2][16] = 28441584;
table[12][2][17] = 64671188;
table[12][2][18] = 134288850;
table[12][2][19] = 260113264;
table[12][2][20] = 476754958;
table[12][2][21] = 835281536;
table[12][2][22] = 409302329;
table[12][2][23] = 302804010;
table[12][2][24] = 660126749;
table[12][3][12] = 1572864;
table[12][3][13] = 11919360;
table[12][3][14] = 50146560;
table[12][3][15] = 155216178;
table[12][3][16] = 395459760;
table[12][3][17] = 880211052;
table[12][3][18] = 774542287;
table[12][3][19] = 318207219;
table[12][3][20] = 849826751;
table[12][3][21] = 837290337;
table[12][3][22] = 915382601;
table[12][3][23] = 931791582;
table[12][3][24] = 2860840;
table[12][4][12] = 9375000;
table[12][4][13] = 74550000;
table[12][4][14] = 325756344;
table[12][4][15] = 37636393;
table[12][4][16] = 697871618;
table[12][4][17] = 80987382;
table[12][4][18] = 328338294;
table[12][4][19] = 38625695;
table[12][4][20] = 374715154;
table[12][4][21] = 192847963;
table[12][4][22] = 199741901;
table[12][4][23] = 142032507;
table[12][4][24] = 31621579;
	cin >> n >> k >> m;
	lag :: init();
	cout << lag :: query(n) << endl;
	return 0;
}
