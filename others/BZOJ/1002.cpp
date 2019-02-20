#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

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

stack <int> s;

struct BigNum
{
	int len, N[100 + 5];
	BigNum() {len = 1;memset(N, 0, sizeof(N));}
	void clear_front_zero()	{while (len > 1 && !N[len]) len--;}
	void output() {DREP(i, len, 1) printf("%d", N[i]);}
	BigNum operator = (int val)
	{
		len = 0;
		do
		{
			N[++len] = val % 10;
			val /= 10;
		}while (val);
		return *this;
	}
	BigNum operator + (BigNum B)
	{
		BigNum c;c.len = max(len, B.len) + 1;
		REP(i, 1, c.len)
		{
			c.N[i] = (c.N[i] + (N[i] * (i <= len) + B.N[i] * (i <= B.len)));
			c.N[i + 1] = c.N[i] / 10;
			c.N[i] %= 10;
		}
		c.clear_front_zero();
		return c;
	}
	BigNum operator - (BigNum B)
	{
		BigNum c;c.len = len;
		REP(i, 1, len) c.N[i] = N[i];
		REP(i, 1, len)
		{
			c.N[i] -= B.N[i] * (i <= B.len);
			if (c.N[i] < 0) c.N[i] += 10, c.N[i + 1]--;
		}
		c.clear_front_zero();
		return c;
	}
	BigNum operator + (int val) {BigNum c;c = val;return *this + c;}
	BigNum operator * (int val) //val < 10
	{
		BigNum c;c.len = len + 1;
		REP(i, 1, len) c.N[i] = N[i];
		REP(i, 1, len) c.N[i] *= val;
		REP(i, 1, len) c.N[i + 1] += c.N[i] / 10, c.N[i] %= 10;
		c.clear_front_zero();
		return c;
	}
}f[100 + 5];

int main()
{
#ifdef CraZYali
	freopen("1002.in", "r", stdin);
	freopen("1002.out", "w", stdout);
#endif
	int n = read<int>();
	f[1] = 1;f[2] = 5;
	REP(i, 3, n) f[i] = f[i-1] * 3 - f[i-2] + 2;
	f[n].output();putchar(10);

	return 0;
}
