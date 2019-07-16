#define REP(i, s, e) for (int i = s; i <= e; i++)
#include <bits/stdc++.h>
using namespace std;
int main()
{
	REP(x,1,500)
		REP(y,1,500)
		REP(z,1,500)
		if ((x^y<=z)^(x^z<=y)){cout<<"FUCK";return 0;}
	return 0;
}
