/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.10 09:10
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
const int maxT = 100 + 5;

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

int prime[60005], p_cnt;
bool notp[60005];
struct __INIT__
{
	__INIT__(const int n = 60000)
	{
		REP(i, 2, n)
		{
			if (!notp[i]) prime[++p_cnt] = i;
			REP(j, 1, p_cnt)
			{
				if (i * prime[j] > n) break;
				notp[i * prime[j]] = 1;
				if (i % prime[j] == 0) break;
			}
		}
	}
}__init__;

inline void output(const vector <int> &A)
{
	DREP(i, (int)A.size() - 1, 0) putchar(A[i] + '0');
	putchar(10);
}

inline bool operator < (const vector <int> &A, const vector <int> &B)
{
	register int lenA = (int)A.size() - 1, lenB = (int)B.size() - 1;
	if (lenA < lenB) return 1;
	if (lenA > lenB) return 0;
	DREP(i, lenA, 0)
		if (A[i] < B[i])
			return 1;
		else if (A[i] > B[i])
			return 0;
	return 0;
}

inline vector <int> operator * (vector <int> A, const int &B)
{
	int len(A.size() - 1);
	REP(i, 0, len) A[i] *= B;
	REP(i, 0, len - 1)
		if (A[i] > 9)
		{
			A[i + 1] += A[i] / 10;
			A[i] %= 10;
		}
	while (A[len] > 9)
	{
		A.push_back(A[len] / 10);
		A[len] %= 10;
		len++;
	}
	while (len && !A[len])
	{
		len--;
		A.pop_back();
	}
	return A;
}

int id[maxT];
vector <int> ans[maxT], ask[maxT];
char s[30000];

inline bool cmp(int x, int y) {return ask[x] < ask[y];}
inline bool operator <= (const vector <int> &A, const vector <int> &B) {return (A < B) || (A == B);}
inline vector <int> operator *= (vector <int> &A, int B) {return A = A * B;}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T(read<int>());
	REP(i, 1, T)
	{
		id[i] = i;
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		ask[i] = vector<int>(n);
		DREP(j, n, 1) ask[i][j-1] = s[n - j + 1] - '0';
	}
	sort(id + 1, id + 1 + T, cmp);
	vector <int> cur(1, 1), tmp(1, 2);
	int j(1);
	REP(I, 1, T)
	{
		int i(id[I]), jj(j-1);
		while (tmp <= ask[i])
		{
			jj++;
			tmp *= prime[jj + 1];
		}
		while (j <= jj)
		{
			cur *= prime[j];
			j++;
		}
		ans[i] = cur;
	}
	REP(i, 1, T)
	{
		DREP(j, (int)ans[i].size() - 1, 0)
			putchar(ans[i][j] + '0');
		putchar(10);
	}
	return 0;
}
