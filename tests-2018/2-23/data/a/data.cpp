#include<bits/stdc++.h>
using namespace std;

const int maxn=4e5+10;
int n,type,m,seed,a[maxn];

inline int rand_(){return rand()&32767;}
inline int r(){return rand_()<<15|rand_();}

int main(int argc,char*argv[]){
	freopen("a.in","w",stdout);
	n=strtol(argv[1],NULL,10);
	type=strtol(argv[2],NULL,10);
	m=strtol(argv[3],NULL,10);
	seed=strtol(argv[4],NULL,10);
	srand(seed);
	printf("%d\n",n);
	if(type!=1){
		for(int i=1;i<=n;++i)
			a[i]=r()%m+1;
	}
	else{
		for(int i=1;i<=n;++i){
			if(a[i])continue;
			int b=r()%(int)round(sqrt(n))+1;
			a[i]=i;
			for(int j=i+b;j<=n&&!a[j]&&r()%100;j+=b)
				a[j]=i;
		}
	}
	for(int i=1;i<=n;++i)
		printf("%d ",a[i]);
	puts("");
	printf("%d\n",n);
	for(int i=1;i<=n;++i){
		int x=r()%n+1,y=r()%n+1;
		if(type==2)
			x=1;
		printf("%d %d\n",min(x,y),max(x,y));
	}
	return 0;
}
