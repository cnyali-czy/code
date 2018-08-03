#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
template<typename T>inline void read(T &x)
{
	T f=1;x=0;char c;
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c^48);
	x*=f;
}
using namespace std;

static int n=10,L=200;

int main()
{
	freopen("queue.in","w",stdout);
	srand(time(NULL));
	cout<<n<<' '<<L<<endl;
	Rep(i,1,n)cout<<rand()*rand()%L<<' ';cout<<endl;
	Rep(i,1,n)cout<<rand()*rand()%L<<' ';cout<<endl;
	return 0;
}

