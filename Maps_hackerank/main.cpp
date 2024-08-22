#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int n, choice, value;
    std::string key;
    std::cin >> n;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

    std::map<std::string, int> maps;


    for (int i{0}; i < n; i++){
      std::cin >> choice;
      // rm buffer
      //std::cin.ignore(numeric_limits<streamsize>::max(), ' ');
      switch(choice){
        case 1:
          {std::cin >> key>> value;
          std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

          // check if the key is already exist
          auto itrm1 = maps.find(key);
          if(itrm1 == maps.end()){
            maps.insert(std::make_pair(key, value));
          }else{
            // the keys already exist
            // save the value of the key
            itrm1->second += value;
          }

          break;}
        case 2:
          {std::cin >> key;
          std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
          maps.erase(key);
          break;}
        case 3:
          {std::cin >> key;
          std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
          auto itrm = maps.find(key); 
          if(itrm == maps.end()){
            std::cout << 0 << std::endl;
          }else{
            
            std::cout << itrm->second << std::endl;
          }

          break;}
        }
    }
    

    return 0;
}



