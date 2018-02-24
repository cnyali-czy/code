#include<bits/stdc++.h>
using namespace std;

int n,k,p,l,r,type,seed;

int rand_(){
	return rand()&32767;
}
int rnd(){
	return rand_()<<15|rand_();
}

int main(int argc,char*argv[]){
	l=strtol(argv[1],NULL,10);
	r=strtol(argv[2],NULL,10);
	type=strtol(argv[3],NULL,10);
	seed=strtol(argv[4],NULL,10);
	freopen("b.in","w",stdout);
	srand(seed);
	n=l+rnd()%(r-l+1);
	if(n<=20){
		while(k<=1||k>=n)
			k=rnd()%(n-2)+2;
	}
	else if(n<=4e2){
		while(k<=n/4||k>=n/2)
			k=rnd()%(n-2)+2;
	}
	else{
		while(k<=n*0.3||k>=n*0.37)
			k=rnd()%(n-2)+2;
	}
	if(type==1){
		k=1;p=n;
	}
	else if(type==2){
		k=n;p=1;
	}
	else if(type==3){
		k=rnd()%(n-2)+2;
		p=n-k+1;
	}
	else if(type==4){
		k=rnd()%(n-2)+2;
		while(p<=n*(n+1)/2)
			p=rnd()%1000000000+1;
	}
	else if(type==5){
		int limit=1;
		for(int i=k+1;i<=n;++i)
			limit+=min(i-k+1,k);
		while(p<=limit)
			p=rnd()%(n*(n+1)/2);
	}
	else{
		int limit=1;
		for(int i=k+1;i<=n;++i)
			limit+=min(i-k+1,k);
loop:
		p=0;
		while(p<=n-k+1)
			p=rnd()%(limit+1);
		if(p<=limit*0.85&&rnd()%100<99)
			goto loop;
	}
	printf("%d %d %d\n",n,k,p);
	return 0;
}
