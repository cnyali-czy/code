#include<bits/stdc++.h>
using namespace std;
#define work system(s)

char s[100];
const int n[]={1e2,1e2,1e2,1e2,5e4,5e4,5e4,5e4,4e5,4e5,4e5,4e5,4e5,4e5,4e5,4e5,4e5,4e5,4e5,4e5};
const int type[]={0,0,0,0,0,0,0,0,0,0,2,2,1,1,1,1,0,0,0,0};
const int m[]={5,10,30,1e2,30,2e2,3e3,5e4,5,10,1e3,2e4,4e5,4e5,4e5,4e5,1e2,1e3,2e4,4e5};

int main(){
	for(int t=1;t<=20;++t){
		sprintf(s,"./data %d %d %d %d\n",n[t-1],type[t-1],m[t-1],time(NULL)+t*t*t*t);
		work;
		sprintf(s,"./a");
		work;
		sprintf(s,"rm a%d.in",t);
		work;
		sprintf(s,"rm a%d.ans",t);
		work;
		sprintf(s,"mv a.in a%d.in",t);
		work;
		sprintf(s,"mv a.out a%d.ans",t);
		work;
		cerr<<t<<endl;
	}
	return 0;
}
