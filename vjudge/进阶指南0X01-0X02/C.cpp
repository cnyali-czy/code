#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 4e4 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int temp[maxn];

struct BigInt
{
	int s[maxn], len;
	BigInt() {memset(s, 0, sizeof(s));len = 0;s[1] = 0;}
	BigInt operator = (int val)
	{
		REP(i, 1, len) s[i] = 0;
		len = 0;
		do
		{
			s[++len] = val % 10;
			val /= 10;
		}while (val);
		return *this;
	}
	BigInt operator * (int val)
	{
		REP(i, 1, len) s[i] *= val;
		BigInt temp;temp = val;
		len += temp.len + 1;
		REP(i, 1, len)
		{
			s[i + 1] += s[i] / 10;
			s[i] %= 10;
		}
		while (!s[len]) len--;
		return *this;
	}
	BigInt operator *= (int val) {return *this = *this * val;}
	void output() {DREP(i, len, 1) printf("%d", s[i]);putchar(10);fflush(stdout);}
}A;

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	int n;
	while (scanf("%d", &n) != EOF)
	{
		A = 1;
		REP(i, 1, n) A *= i;
		A.output();
	}
	return 0;
}
