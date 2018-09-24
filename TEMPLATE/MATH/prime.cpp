#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 10;

vector <int> prime;
int prime_cnt;

bool notprime[MAX];

void getprime(int n)
{
	prime.push_back(0);
	REP(i, 2, n)
	{
		if (!notprime[i])
		{
			prime.push_back(i);
			prime_cnt++;
		}
		REP(j, 1, prime_cnt)
		{
			if (prime[j] > i || i * prime[j] > n) break;
			notprime[prime[j] * i] = 1;
		}
	}
}

int m, n, k;

int main(){return 0;}
