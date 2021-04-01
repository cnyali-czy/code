#include"testlib.h"

int n,Q;

int main(){
	registerValidation();
	n=inf.readInt(2,100000,"n");
	inf.readSpace();
	Q=inf.readInt(0,100000,"Q");
	inf.readEoln();
	for (int i=1;i<n;i++){
		inf.readInt(1,i,format("f%d",i+1));
		i==n-1?inf.readEoln():void(inf.readSpace());
	}
	while (Q--){
		int opt;
		opt=inf.readInt(1,2,"k");
		inf.readSpace();
		inf.readInt(1,n,"x");
		inf.readSpace();
		if (opt==1) inf.readInt(0,359,"theta");
		else inf.readInt(1,n,"y");
		inf.readEoln();
	}
	inf.readEof();
}
