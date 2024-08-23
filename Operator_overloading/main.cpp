#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{
public:
	std::vector<std::vector<int>> a;
	Matrix(){

	}
	Matrix& operator+(Matrix const &rhs){
		// Matrix temp;
		// vector<int> b;
		for (int i = 0; i < this->a.size(); i++)
		{
			for (int j = 0; j < this->a[i].size(); j++){
				//b.push_back(this->a[i][j] + rhs.a[i][j]);
				this->a[i][j] += rhs.a[i][j];
			}
			//temp.a.push_back(b);
		}
		//return temp;
		return *this;
	}
};

int main () {
   int cases,k;
   cin >> cases;
   for(k=0;k<cases;k++) {
      Matrix x;
      Matrix y;
      Matrix result;
      int n,m,i,j;
      cin >> n >> m;
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         x.a.push_back(b);
      }
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         y.a.push_back(b);
      }
      result = x+y;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }
			
   }  
   return 0;
}
