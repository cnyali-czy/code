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

const int MAXN=3e5+7;

static int n=300000,p[MAXN],di=n*0.46;

int main()
{
	freopen("run10.in","w",stdout);
	cout<<n<<endl;
	Rep(i,1,n)p[i]=i;
	srand(time(NULL));
	random_shuffle(p+1,p+n+1);
	//Rep(i,2,n)cout<<p[i]<<' '<<p[i]/2<<endl;
	Rep(i,1,di)cout<<p[i]<<' '<<p[i+1]<<endl;
	Rep(i,di+2,n)cout<<p[i]<<' '<<p[rand()*rand()%(i-di-1)+1]<<endl;
	cout<<rand()*rand()%n+1<<' '<<rand()*rand()%n+1<<' '<<rand()*rand()%n+1<<endl;
	return 0;
}

