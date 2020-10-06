#include <vector>
#include "perm.h"
std::vector<int> guess(int n){
	std::vector<int> ret;
	for(int i=1;i<=n;++i) ret.push_back(i);
	return ret;
}