#include<bits/stdc++.h>
using namespace std;

int rand_(){return rand()&32767;}
int r(){return rand_()<<15|rand_();}

int main(int argc,char*argv[]){
	freopen("c.in","w",stdout);
	int n=strtol(argv[1],NULL,10),m=n;
	int type=strtol(argv[2],NULL,10),seed=strtol(argv[3],NULL,10);
	srand(seed);
	n-=r()%n/20;
	m-=r()%m/20;
	printf("%d %d\n",n,m);
	for(int i=1;i<=m;++i){
		int t=rand()%3+1,color=rand()&1;
		if(type==1&&t!=1){--i;continue;}
		if(type==2&&t==3){--i;continue;}
		if(type==3&&color!=0){--i;continue;}
		if(t<=2)
			printf("%d %d %d\n",t,rand()%n+1,color);
		else
			printf("%d %d %d\n",3,rand()%(2*n-1)+2,color);
	}
	return 0;
}
