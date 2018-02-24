#include<bits/stdc++.h>
using namespace std;
#define work system(s)

char s[100];
const int n[]={1e3,1e3,1e3,1e3,1e3,1e5,1e5,1e5,1e5,1e5,1e5,1e5,1e5,1e5,1e5,1e5,1e5,1e5,1e5,1e5};
const int type[]={0,0,0,0,0,1,1,2,2,2,2,3,3,3,3,3,0,0,0,0};

int main(){
	for(int t=1;t<=20;++t){
		sprintf(s,"./data %d %d %d\n",n[t-1],type[t-1],time(NULL)+t*t*t*t);
		work;
		sprintf(s,"./c");
		work;
		sprintf(s,"rm c%d.in",t);
		work;
		sprintf(s,"rm c%d.ans",t);
		work;
		sprintf(s,"mv c.in c%d.in",t);
		work;
		sprintf(s,"mv c.out c%d.ans",t);
		work;
		cerr<<t<<endl;
	}
	return 0;
}
