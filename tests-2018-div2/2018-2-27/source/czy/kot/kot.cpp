#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k;

int A[300];

inline void turn(char &c){if ('a' <= c && c <= 'z') c = c - 'a' + 'A';}

int main()
{
	freopen("kot.in", "r", stdin);
	freopen("kot.out", "w", stdout);
	A['`'] = A['-'] = A['='] = 1;
	REP(i, '0', '9') A[i] = 1;
	A['Q'] = A['W'] = A['E'] = A['R'] = A['T'] = A['Y'] = A['U'] = A['I'] = A['O'] = A['P'] = A['['] = A[']'] = A['\\'] = 2;
	A['A'] = A['S'] = A['D'] = A['F'] = A['G'] = A['H'] = A['J'] = A['K'] = A['L'] = A[';'] = A['\''] = 3;
	A['Z'] = A['X'] = A['C'] = A['V'] = A['B'] = A['N'] = A['M'] = A[','] = A['.'] = A['/'] = 4;
	A[' '] = 5;
	register char c = getchar();
	while (c != '\n' && c != '\r')
	{
		turn(c);
		printf("%d", A[c]);
		c = getchar();
	}

	return 0;
}
