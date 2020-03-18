/*
	Problem:	A.cpp
	Time:		2020-02-23 08:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <set>
#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 5000;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], SG[maxn];
//unordered_map <int, int> Map;
bitset <maxn> show;

namespace run
{
	int f[maxn][20], sum[maxn], lg[maxn], v[maxn];
	struct __init__
	{
		__init__(const int n = maxn - 10)
		{
			REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
		}
	}__INIT__;
	int query(int l, int r)
	{
		if (l == r) return 0;
		int ans = 0;
		DEP(i, lg[r - l + 1], 0) if (l + (1 << i) - 1 <= r)
		{
			ans ^= f[l][i] ^ ((sum[r] ^ sum[l + (1 << i) - 1]) << i);
			l += 1 << i;
		}
		return ans;
	}
	int main()
	{
		n = read<int>();
		REP(i, 1, n) v[read<int>()] ^= 1;
		REP(i, 1, n) sum[i] = sum[i - 1] ^ v[i];
		REP(j, 1, 19)
			REP(i, 0, n - (1 << j) + 1)
			f[i][j] = f[i][j-1] ^ f[i + (1 << j - 1)][j-1] ^ ((sum[i + (1 << j) - 1] ^ sum[i + (1 << j - 1) - 1]) << j - 1);
		REP(i, 1, n)
		{
			int hhakioi = 0;
			for (int j = 0; j <= n; j += i + 1)
				hhakioi ^= query(j, min(j + i, n));
			if (hhakioi) cout << "Alice ";
			else cout << "Bob ";
		}
		return 0;
	}
}


int main()
{
#ifdef CraZYali
	file("A");
#endif
	return run::main();
	n = read<int>();
	int Max = 0;
	REP(i, 1, n) a[i] = read<int>(), chkmax(Max, a[i]);
	REP(x, 1, n)
	{
		//		Map.clear();Map[0] = 1;
		show.set();show[0] = 0;
		REP(i, 1, Max)
		{
			if (i > x)
			{
				show[SG[i - x - 1]] = 1;
				//				Map[SG[i - x - 1]]--;
				//				if (!Map[SG[i - x - 1]]) Map.erase(SG[i - x - 1]);
			}
			SG[i] = show._Find_first();
			//			REP(j, 0, 114514) if(!Map.count(j) || !Map[j]){SG[i]=j;break;}
			show[SG[i]] = 0;
			//			Map[SG[i]]++;
		}
		int res = 0;
		REP(i, 1, n) res ^= SG[a[i]];
		printf("%s ", res ? "Alice" : "Bob");
	}
	return 0;
}
