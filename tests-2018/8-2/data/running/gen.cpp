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
const int MAXN=1e6+7;
static int n=1000000;
static int p[MAXN];
int main()
{
	freopen("running.in","w",stdout);
	srand(time(NULL));
	cout<<n<<endl;
	Rep(i,1,n)p[i]=i;
	random_shuffle(p+1,p+n+1);
	Rep(i,1,n-1)cout<<p[i+1]<<' '<<p[rand()*rand()%i+1]<<endl;
	Rep(i,1,n)cout<<rand()%35<<' ';cout<<endl;
	return 0;
}

