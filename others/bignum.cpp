/*
	Problem:	bignum.cpp
	Time:		2020-09-20 21:38
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;

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

namespace BigNum
{
	const int bin[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
	const int w = 4, base = bin[w];
	const int maxlen = 3000 + 10;
	char s[maxlen];
	inline int get(int val, int p)
	{
		return val / bin[w - p] % 10;
	}
	struct num
	{
		vector <int> v;
		int& operator [] (int x) {return v[x];}
		num()
		{
			v.clear();
			v.resize(1);
		}
		void clearzero()
		{
			while (v.size() && !v.back()) v.pop_back();
		}
		void input()
		{
			scanf("%s", s + 1);
			if (s[1] == '0')
			{
				num();
				return;
			}
			int x = 0;
			v.clear();
			int cnt = 0;
			DEP(i, strlen(s + 1), 1)
			{
				x += bin[cnt++] * (s[i] - 48);
				if ((cnt) == w)
				{
					v.push_back(x);
					cnt = x = 0;
				}
			}
			if (x) v.push_back(x);
		}
		void output()
		{
			printf("%d", v.back());
			DEP(i, (int)v.size() - 2, 0)
			{
				REP(j, 1, w) putchar(get(v[i], j) + 48);
			}
		}
	};
	inline num operator + (num C, num B)
	{
		C.v.resize(max(C.v.size(), B.v.size()) + 1);
		REP(i, 0, B.v.size() - 1)
		{
			C[i] += B[i];
			if (C[i] >= base)
			{
				C[i + 1] += C[i] / base;
				C[i] %= base;
			}
		}
		C.clearzero();
		return C;
	}
	inline num operator - (num C, num B)//C >= B
	{
		REP(i, 0, B.v.size() - 1) C[i] -= B[i];
		REP(i, 0, C.v.size() - 1)
		{
			if (C[i] < 0)
			{
				int tmp = (base - 1 -C[i]) / base;
				C[i] += tmp * base;
				C[i + 1] -= tmp;
			}
		}
		C.clearzero();
		return C;
	}
	inline num operator * (num A, num B)
	{
		static i64 tmp[maxlen];
		REP(i, 0, A.v.size() + B.v.size() - 1) tmp[i] = 0;
		REP(i, 0, A.v.size() - 1)
			REP(j, 0, B.v.size() - 1)
			tmp[i + j] += A[i] * B[j];
		REP(i, 0, A.v.size() + B.v.size() - 1)
			if (tmp[i] >= base)
			{
				tmp[i + 1] += tmp[i] / base;
				tmp[i] %= base;
			}
		num C;
		C.v.resize(A.v.size() + B.v.size());
		REP(i, 0, A.v.size() + B.v.size() - 1)
			C[i] = tmp[i];
		C.clearzero();
		return C;
	}
}
using namespace BigNum;

int main()
{
#ifdef CraZYali
	file("bignum");
#endif
	num A, B;
	A.input();B.input();
	(A - B).output();
	return 0;
}
