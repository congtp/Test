/* Enter your macros here */

#define toStr(x) #x
#define io(v) std::cin >> v
#define INF INT32_MAX
#define foreach(v, i) for(int i = 0; i < v.size(); i++)
#define FUNCTION(fcn, op) void fcn(int& a, int b) { if (b op a) a = b; }

#include <iostream>
#include <vector>
using namespace std;

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif 

FUNCTION(minimum, <)
FUNCTION(maximum, >)

int main(){
    std::cout << INF;
    int n;
    cin >> n;
    vector<int> v(n);
	foreach(v, i) {
		io(v)[i];
	}
	int mn = INF;
	int mx = -INF;
	foreach(v, i) {
		minimum(mn, v[i]);
		maximum(mx, v[i]);
	}
	int ans = mx - mn;
	cout << toStr(Result =) <<' '<< ans;
	return 0;

}