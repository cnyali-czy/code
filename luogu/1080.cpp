#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, maxlen = 10000;

template <typename T> inline T read()
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;
pair <int, int> a[maxn];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first * A.second < B.first * B.second;}

struct BIGINT
{
	int s[maxlen], len;
	BIGINT() {len = 1;memset(s, 0, sizeof(s));}
	BIGINT operator = (int x) 
	{
		len = 0;
		do
		{
			s[++len] = x % 10;
			x /= 10;
		}while (x);
		s[len + 1] = 0;
		return *this;
	}
	BIGINT operator + (int x)
	{
		register int now = 1;
		while (x)
		{
			s[now] += x % 10;
			x /= 10;
			if (s[now] > 9)
			{
				s[now + 1] += s[now] / 10;
				s[now] %= 10;
			}
			now++;
		}
		if (s[now] > 9)
		{
			s[now + 1] += s[now] / 10;
			s[now] %= 10;
			now++;
		}
		while (!s[now]) now--;
		chkmax(len, now);
		return *this;
	}
	BIGINT operator + (BIGINT B)
	{
		BIGINT C;
		int &pos = C.len;
		while (pos <= len || pos <= B.len)
		{
			C.s[pos] += s[pos] + B.s[pos];
			C.s[pos + 1] += C.s[pos] / 10;
			C.s[pos] %= 10;
			pos++;
		}
		while (pos > 0 && C.s[pos] == 0) pos--;
		return C;
	}
	BIGINT operator += (BIGINT B) {return *this = *this + B;}
	bool operator >= (BIGINT B)
	{
		if (len > B.len) return 1;
		else if (len < B.len) return 0;
		else
		{
			REP(i, 1, len)
				if (s[i] >= B.s[i]) return 1;
			return 0;
		}
	}
	BIGINT operator - (BIGINT B)
	{
		BIGINT A = *this;
		if (A.len < B.len) swap(A, B);
		REP(i, 1, A.len)
		{
			A.s[i] -= B.s[i];
			while (A.s[i] < 0)
			{
				A.s[i] += 10;
				A.s[i + 1]--;
			}
		}
		while (A.len && !A.s[A.len]) A.len--;
		return A;
	}
	BIGINT operator -= (BIGINT B) {return *this = *this - B;}
	BIGINT operator * (BIGINT B)
	{
		BIGINT tot;
		REP(i, 1, B.len)
		{
			BIGINT temp;
			REP(j, 1, len)
			{
				temp
			}
		}
	}
	//make sure call - before checked A >= B
	
}res, ans;

ostream& operator << (ostream& out, BIGINT A) {DREP(i, A.len, 1) out << A.s[i];return out;};
int main()
{
#ifdef CraZYali
	freopen("1080.in", "r", stdin);
	freopen("1080.out", "w", stdout);
#endif
	BIGINT A ;A= 123;BIGINT B;B = 99;cout << (A - B);
	n = read<int>();
	REP(i, 1, n + 1) a[i].first = read<int>(), a[i].second = read<int>(); 
	n++;
	sort(a + 2, a + 1 + n, cmp);
	res = a[1].first;
	REP(i, 2, n)
	{
		
	}
	return 0;
}
