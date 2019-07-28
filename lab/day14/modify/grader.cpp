#include <cstdlib>
#include <cstdio>
#include "polynomial.h"

const int _P=998244353;
int _N,_M,_T,_A[10001],_MODE;

void error(int _TYPE)
{
	printf("Error type:%d\n",_TYPE);
	exit(_TYPE);
}

void check1(int i)
{
	if ((i<1)||(_T<i))  error(3);
}

void check2(int i)
{
	if ((i<=_N)||(_T<i))  error(3);
}

void Set(int i,int x)
{
	if (_MODE)  error(1);
	check2(i);
	_A[i]=x;
}

void Plus(int i,int j,int k)
{
	if (!_MODE)  error(2);
	check2(i),check1(j),check1(k);
	_A[i]=(_A[j]+_A[k])%_P;
}

void Minus(int i,int j,int k)
{
	if (!_MODE)  error(2);
	check2(i),check1(j),check1(k);
	_A[i]=(_A[j]-_A[k]+_P)%_P;
}

void Multiply(int i,int j,int k)
{
	if (!_MODE)  error(2);
	check2(i),check1(j),check1(k);
	_A[i]=1LL*_A[j]*_A[k]%_P;
}

void Answer(int i)
{
	check1(i);
	printf("%d\n",_A[i]);
	exit(0);
}

int main()
{
	scanf("%d %d %d",&_N,&_M,&_T);
	for (int i=1; i<=_N; i++)
		scanf("%d",&_A[i]);
	_MODE=0;
	Init(_N,_M,_T);
	_MODE=1;
	Solve();
	error(4);
	return 0;
}
